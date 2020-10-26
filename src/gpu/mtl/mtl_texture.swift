
import Metal
import MetalKit
import Darwin

import mtl_start

extension StartMTL {

	public func createTexture(d device:MTLDevice, w width:Int, h height:Int) -> Int32 {

		let texture_width = width
		let texture_height = height
		let texture_stride = getStride(width: width)

		let textureDesc = MTLTextureDescriptor()
		textureDesc.width = texture_width
		textureDesc.height = texture_height
		textureDesc.usage = .shaderRead

		textureDesc.pixelFormat = MTLPixelFormat.bgra8Unorm
		let texture_buff = device.makeBuffer(length: texture_stride * height)
		let texture = texture_buff?.makeTexture(descriptor:textureDesc, offset:0, bytesPerRow:texture_stride)

		if (texture != nil) {
			let index = textures.count
			textures.append(texture!)
			return (Int32(index))
		}
		return (Int32(-1))
	}

	public func getStride(width : Int) -> Int {
//		texture_sizeline = width * 4
//		texture_sizeline = 256 * (texture_sizeline / 256 + (texture_sizeline%256 >= 1 ? 1 : 0) )
		let stride = width * 4;
		return (256 * (stride / 256 + (stride%256 >= 1 ? 1 : 0)))
	}

	public func getTexturePointer(index i:Int) -> UnsafeMutablePointer<UInt32>? {
		if (i < 0 || i >= textures.count) {
			return (nil);
		}
		guard let tmpptr = textures[i].buffer?.contents() else {return (nil)}
		return (tmpptr.assumingMemoryBound(to:UInt32.self))
	}

	public func getTextureStride(index: Int32) -> Int32 {
		let i = Int(index)
		guard (i >= 0 && i < textures.count) else { return Int32(0) }

		print("swift stride is \(getStride(width: (textures[i]).width))")
		return (Int32(getStride(width: (textures[i]).width)))
	}

	public func getTextureWidth(index i : Int32) -> Int32 {
		guard (i < 0 || i >= textures.count) else { return Int32(0) }
		return (Int32(textures[Int(i)].width))
	}

	public func getTextureHeight(index i : Int32) -> Int32 {
		guard (i < 0 || i >= textures.count) else { return Int32(0) }
		return (Int32(textures[Int(i)].height))
	}
}

