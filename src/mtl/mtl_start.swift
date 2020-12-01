
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
	public var targetTextures = [MTLTexture]()

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

		guard let lib = library else {
			print("mtl: metal shader library is not loaded"); return Int32(1)
		}

		guard infoBuffer != nil  && objectsBuffer != nil && materialsBuffer != nil else {
			print("mtl: metal buffers are not loaded"); return Int32(1)
		}

		guard (textureID >= 0 && textureID < targetTextures.count) else {
			print("mtl: invalid target texture index"); return Int32(1)
		}
		let textureOut = targetTextures[textureID]


		guard let queue = device.makeCommandQueue() else {
			print("mtl: cannot create metal queue"); return Int32(1)
		}

		guard let kernel = lib.makeFunction(name: name) else {
			print("mtl: cannot create metal kernel"); return Int32(1)
		}

		guard let pipelineState = try? device.makeComputePipelineState(function: kernel) else {
			print("mtl: cannot create metal pipeline state"); return Int32(1)
		}

		guard let buffer = queue.makeCommandBuffer() else {
			print("mtl: cannot create metal queue buffer"); return Int32(1)
		}

		// encoding arguments
		// encoding scene argument
		let sceneArgumentEncoder = kernel.makeArgumentEncoder(bufferIndex: 0)
		guard let sceneBuffer = device.makeBuffer(length: sceneArgumentEncoder.encodedLength, options: []) else {
			print("mtl: cannot create scene buffer"); return Int32(1)
		}
		sceneArgumentEncoder.setArgumentBuffer(sceneBuffer, offset: 0)
		sceneArgumentEncoder.setBuffer(infoBuffer, offset: 0, index: 0)
		sceneArgumentEncoder.setBuffer(objectsBuffer, offset: 0, index: 1)
		sceneArgumentEncoder.setBuffer(materialsBuffer, offset: 0, index: 2)

		// encoding textures argument
		let texturesArgumentEncoder = kernel.makeArgumentEncoder(bufferIndex: 1)
		let oneTextureArgumentLength = texturesArgumentEncoder.encodedLength
		// texturesArgumentEncoder encodes an array so we multiply by textures count
		let textureBufferLength = oneTextureArgumentLength * (textures.count)
		guard let textureResBuffer = device.makeBuffer(length: textureBufferLength, options: []) else {
			print("mtl: cannot create texture buffer"); return Int32(1)
		}

		// also works insteda of (setArgumentBuffer(_, startOffset:, arrayElement:)
		// texturesArgumentEncoder.setArgumentBuffer(textureResBuffer, offset: oneTextureArgumentLength * i)
		for i in 0..<textures.count {
			texturesArgumentEncoder.setArgumentBuffer(textureResBuffer, startOffset: 0, arrayElement: i)
			texturesArgumentEncoder.setTexture(textures[i], index: 0)
		}

		// setting buffers
		guard let computeEncoder = buffer.makeComputeCommandEncoder() else { return Int32(1) }
		computeEncoder.setComputePipelineState(pipelineState)
		computeEncoder.setBuffer(sceneBuffer, offset: 0, index: 0)
		computeEncoder.setBuffer(textureResBuffer, offset: 0, index: 1)
		computeEncoder.setTexture(textureOut, index: 2)

		// resource using rules
		for i in 0..<textures.count {
			computeEncoder.useResource(textures[i], usage: MTLResourceUsage.read)
		}
		computeEncoder.useResource(infoBuffer!, usage: MTLResourceUsage.read)
		computeEncoder.useResource(objectsBuffer!, usage: MTLResourceUsage.read)
		computeEncoder.useResource(materialsBuffer!, usage: MTLResourceUsage.read)
		computeEncoder.useResource(textureOut, usage: MTLResourceUsage.write)

		// prepare to run
		let threadsPerThreadgroup = MTLSize(width: 32, height: 16, depth: 1)
		let numGroups = MTLSize(width: 1 + textureOut.width/threadsPerThreadgroup.width, height: 1 + textureOut.height/threadsPerThreadgroup.height, depth: 1)
		computeEncoder.dispatchThreadgroups(numGroups, threadsPerThreadgroup: threadsPerThreadgroup)
		computeEncoder.endEncoding()

		guard let blitEncoder = buffer.makeBlitCommandEncoder() else { return Int32(1) }
		blitEncoder.synchronize(resource: textureOut)
		blitEncoder.endEncoding()

		buffer.commit()
		buffer.waitUntilCompleted()

		if let _ = buffer.error {
			print("mtl: metal kernel run failed");
			print("mtl: error_str: \(String(describing:buffer.error))")
			return Int32(1)
		}
		return Int32(0)
	}
}
