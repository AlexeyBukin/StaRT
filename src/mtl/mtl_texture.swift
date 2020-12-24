
import Metal
import MetalKit
import Darwin

import mtl_start

extension StartMTL {

	func	addTextureTarget(_ newTarget: MTLTexture?) -> Int32 {
		if (newTarget != nil) {
			let index = targetTextures.count
			targetTextures.append(newTarget!)
			return (Int32(index))
		}
		return (Int32(-1))
	}

	func	addTextureResource(_ newResource: MTLTexture?) -> Int32 {
		if (newResource != nil) {
			let index = textures.count
			textures.append(newResource!)
			return (Int32(index))
		}
		return (Int32(-1))
	}

	public func	loadTextureResourceRGBA8(data ptr: UnsafeRawPointer, width:Int, height:Int) -> Int32 {
		let textureDesc = MTLTextureDescriptor()
		textureDesc.width = width
		textureDesc.height = height
		textureDesc.usage = .shaderRead
		textureDesc.pixelFormat = MTLPixelFormat.rgba8Unorm

		let stride = 4 * width;
		let texture_buff = device.makeBuffer(bytes: ptr, length: stride * height, options: [])
		let texture = texture_buff?.makeTexture(descriptor:textureDesc, offset:0, bytesPerRow:stride)

		return (addTextureResource(texture))
	}

	public func createTexture(d device:MTLDevice, w width:Int, h height:Int) -> Int32 {

		let texture_width = width
		let texture_height = height
		//.TODO split to createTextureRGBA8 and other
		var texture_stride = 4 * width
		texture_stride = 256 * (texture_stride / 256 + (texture_stride % 256 >= 1 ? 1 : 0))
		//getStride(width: width)
		let textureDesc = MTLTextureDescriptor()
		textureDesc.width = texture_width
		textureDesc.height = texture_height
		textureDesc.usage = .shaderWrite

		textureDesc.pixelFormat = MTLPixelFormat.rgba8Unorm
		let texture_buff = device.makeBuffer(length: texture_stride * height)
		let texture = texture_buff?.makeTexture(descriptor:textureDesc, offset:0, bytesPerRow:texture_stride)

		return (addTextureTarget(texture))
	}

	public func getTexturePointer(index i:Int) -> UnsafeMutablePointer<UInt32>? {
		if (i < 0 || i >= targetTextures.count) {
			return (nil);
		}
		guard let tmpptr = targetTextures[i].buffer?.contents() else {return (nil)}
		return (tmpptr.assumingMemoryBound(to:UInt32.self))
	}

    public func getTargetWidth(index i : Int32) -> Int32 {
		guard (i < 0 || i >= targetTextures.count) else { return Int32(0) }
		return (Int32(targetTextures[Int(i)].width))
	}

	public func getTargetHeight(index i : Int32) -> Int32 {
    	guard (i < 0 || i >= targetTextures.count) else { return Int32(0) }
    	return (Int32(targetTextures[Int(i)].height))
    }

	public func getTextureWidth(index i : Int32) -> Int32 {
		guard (i < 0 || i >= textures.count) else { return Int32(0) }
		return (Int32(textures[Int(i)].width))
	}

	public func getTextureHeight(index i : Int32) -> Int32 {
		guard (i < 0 || i >= textures.count) else { return Int32(0) }
		return (Int32(textures[Int(i)].height))
	}

	func makeCGImage(for texture: MTLTexture) -> CGImage? {
		assert(texture.pixelFormat == .rgba8Unorm)

		let width = texture.width
		let height = texture.height
		let pixelByteCount = 4 * MemoryLayout<UInt8>.size
		let imageBytesPerRow = width * pixelByteCount
		let imageByteCount = imageBytesPerRow * height
		let imageBytes = UnsafeMutableRawPointer.allocate(byteCount: imageByteCount, alignment: pixelByteCount)
		defer {
			imageBytes.deallocate()
		}

		texture.getBytes(imageBytes,
				bytesPerRow: imageBytesPerRow,
				from: MTLRegionMake2D(0, 0, width, height),
				mipmapLevel: 0)

		guard let colorSpace = CGColorSpace(name: CGColorSpace.linearSRGB) else { return nil }
		let bitmapInfo = CGImageAlphaInfo.premultipliedLast.rawValue
		guard let bitmapContext = CGContext(data: nil,
				width: width,
				height: height,
				bitsPerComponent: 8,
				bytesPerRow: imageBytesPerRow,
				space: colorSpace,
				bitmapInfo: bitmapInfo) else { return nil }
		bitmapContext.data?.copyMemory(from: imageBytes, byteCount: imageByteCount)
		let image = bitmapContext.makeImage()
		return image
	}

	func saveTextureAsPNG(_ texture: MTLTexture, path: String) -> Int32 {
		guard let image = makeCGImage(for: texture) else { return Int32(-1) }
		guard let fileUrl = URL(string: path)  else { return Int32(-1) }

		print("mtl: saving as png...")
		print(fileUrl)

		if let imageDestination = CGImageDestinationCreateWithURL(fileUrl as CFURL, kUTTypePNG as CFString, 1, nil) {
			print("mtl: saving as png...")
			CGImageDestinationAddImage(imageDestination, image, nil)
			CGImageDestinationFinalize(imageDestination)
		} else {
//			print("mtl: cannot save image")
			return (Int32(-1))
		}
		return (Int32(0))
	}

	public func saveTargetTextureAsPNG(index i: Int, path: String) -> Int32 {
		guard (i >= 0 && i <= targetTextures.count) else { return Int32(-1) }
		return (saveTextureAsPNG(targetTextures[i], path: path))
	}
}

