
//import Cocoa

import Metal
//import MetalKit
import Darwin

public class StartMTL {

	public var device:MTLDevice!
	public var library:MTLLibrary?

	public var bufNamedList = [String : MTLBuffer]()
	public var arguments = [MTLArgumentDescriptor]()

	public var sceneBuffer = MTLBuffer?
	public var objectsBuffer = MTLBuffer?
	public var materialsBuffer = MTLBuffer?

	public var textures = [MTLTexture]()
	public var models = [MTLBuffer]()

	public init() {
		device = MTLCreateSystemDefaultDevice()!
		library = nil
	}

	public func loadLibrary(source: String) -> Int32 {
		do {
			library = try device.makeLibrary(source: source, options: nil)
		} catch {
			print("Unexpected error: \(error).")
			library = nil
			return Int32(1)
		}
		return Int32(0)
	}
}

extension StartMTL {

	public func addTexture(d device:MTLDevice, w width:Int, h height:Int) -> Int32 {

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
		let stride = width * 4;
		return (256 * (stride / 256 + (stride%256 >= 1 ? 1 : 0) ))
	}

	public func getTexturePointer(index i:Int) -> UnsafeMutablePointer<UInt32>? {
		if (i < 0 || i >= textures.count) {
			return (nil);
		}
		guard let tmpptr = textures[i].buffer?.contents() else {return (nil)}
		return (tmpptr.assumingMemoryBound(to:UInt32.self))
	}

	public func getTextureStride(index i : Int32) -> Int32 {
		guard (i < 0 || i >= textures.count) else { return Int32(0) }
		return (Int32(getStride(width: (textures[Int(i)]).width)))
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

extension StartMTL {

	public func loadSceneBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		guard let sceneBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: []) else { return (Int32(1)) }
		return Int32(0)
	}

	public func loadObjectsBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		guard let objectsBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: []) else { return (Int32(1)) }
		return Int32(0)
	}

	public func loadMaterialsBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		guard let materialsBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: []) else { return (Int32(1)) }
		return Int32(0)
	}

}
