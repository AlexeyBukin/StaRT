
import Metal
//import MetalKit
import Darwin

public class StartMTL {

	public var device:MTLDevice!
	public var library:MTLLibrary?

	public var bufNamedList = [String : MTLBuffer]()
	public var arguments = [MTLArgumentDescriptor]()

	public var infoBuffer : MTLBuffer?
	public var objectsBuffer : MTLBuffer?
	public var materialsBuffer : MTLBuffer?
	public var texturesBuffer : MTLBuffer?

	public var textures = [MTLTexture]()
//	public var models = [MTLBuffer]()

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

		guard infoBuffer != nil  && objectsBuffer != nil && materialsBuffer != nil else { return Int32(1) }
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

		let materialArgumentEncoder = kernel.makeArgumentEncoder(bufferIndex: 0)
		let argumentBufferLength = materialArgumentEncoder.encodedLength

//		_sourceTextures = [_device newBufferWithLength:argumentBufferLength options:0];
		print("my aglen: \(argumentBufferLength)")
		guard let sourceMaterials = device.makeBuffer(length: argumentBufferLength, options: []) else { print("cannot malloc buffer on gpu"); return Int32(1) }

//		print()
//		sourceMaterials.label = "Texture List"
		materialArgumentEncoder.setArgumentBuffer(sourceMaterials, offset: 0)
		materialArgumentEncoder.setTexture(textures[0], index: 0)
		materialArgumentEncoder.setBuffer(materialsBuffer, offset: 0, index: 1)
		let constantPointer = materialArgumentEncoder.constantData(at: 2)
		constantPointer.storeBytes(of: 0.2, as: Float.self)

//		materialArgumentEncoder.setArgumentBuffer(materialsBuffer, offset: 0)
//		let materialEncoder = kernel.makeArgumentEncoder(bufferIndex: 2);// else { return Int32(1) }
//		materialEncoder.setArgumentBuffer(materialsBuffer, offset: 0)
//		materialArgumentEncoder.setTexture(textures[1], index: 0)

		guard let computeEncoder = buffer.makeComputeCommandEncoder() else { return Int32(1) }
		computeEncoder.setComputePipelineState(pipelineState)
//		computeEncoder.setBuffer(infoBuffer, offset: 0, index: 0)
//		computeEncoder.setBuffer(objectsBuffer, offset: 0, index: 1)
		computeEncoder.setBuffer(sourceMaterials, offset: 0, index: 0)
		computeEncoder.useResource(textures[0], usage: MTLResourceUsage.read)
		computeEncoder.useResource(materialsBuffer!, usage: MTLResourceUsage.read)
//		computeEncoder.setTexture(textures[0], index: 0)
		computeEncoder.setTexture(textureOut, index: 1)

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
