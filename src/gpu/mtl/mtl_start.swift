
import Metal
//import MetalKit
import Darwin

public class StartMTL {

	public var device:MTLDevice!
	public var library:MTLLibrary?

	public var bufNamedList = [String : MTLBuffer]()
	public var arguments = [MTLArgumentDescriptor]()

	public var sceneBuffer : MTLBuffer?
	public var objectsBuffer : MTLBuffer?
	public var materialsBuffer : MTLBuffer?

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
