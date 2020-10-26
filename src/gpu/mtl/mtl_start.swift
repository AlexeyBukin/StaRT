
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

	public func runStartKernel(name: String, textureID: Int) -> Int32 {

		guard let lib = library else { return Int32(1) }
		print("metal lib ready")

		guard sceneBuffer != nil  && objectsBuffer != nil && materialsBuffer != nil else { return Int32(1) }
		print("metal basic buffers ready")

//		print("SWIFT: textureID is \(textureID)")
		guard (textureID >= 0 && textureID < textures.count) else { return Int32(1) }
		let textureOut = textures[textureID]
		print("metal out texture ready")

		guard let queue = device.makeCommandQueue() else {  return Int32(1) }
		print("metal queue ready")

		guard let kernel = lib.makeFunction(name: name) else { return Int32(1) }
		print("metal kernel ready")

		guard let pipelineState = try? device.makeComputePipelineState(function: kernel) else { return Int32(1) }
		print("metal pipeline state ready")

		guard let buffer = queue.makeCommandBuffer() else { return Int32(1) }
		print("metal queue buffer ready")

		guard let computeEncoder = buffer.makeComputeCommandEncoder() else { return Int32(1) }
		computeEncoder.setComputePipelineState(pipelineState)
		computeEncoder.setBuffer(sceneBuffer, offset: 0, index: 0)
		computeEncoder.setBuffer(objectsBuffer, offset: 0, index: 1)
		computeEncoder.setBuffer(materialsBuffer, offset: 0, index: 2)
		computeEncoder.setTexture(textureOut, index: 3)

		let threadsPerThreadgroup = MTLSize(width: 32, height: 16, depth: 1)
		let numGroups = MTLSize(width: 1 + textureOut.width/threadsPerThreadgroup.width, height: 1 + textureOut.height/threadsPerThreadgroup.height, depth: 1)
		computeEncoder.dispatchThreadgroups(numGroups, threadsPerThreadgroup: threadsPerThreadgroup)
		computeEncoder.endEncoding()

		guard let blitEncoder = buffer.makeBlitCommandEncoder() else { return Int32(1) }
		blitEncoder.synchronize(resource: textureOut)
		blitEncoder.endEncoding()

		buffer.commit()
		buffer.waitUntilCompleted()

		if let _ = buffer.error { print("metal kernel run failed"); return Int32(1) }

		print("metal kernel run success")
		return Int32(0)
	}
}
