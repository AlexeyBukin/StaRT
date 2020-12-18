
import Metal
import MetalKit
import Darwin

import mtl_start

extension StartMTL {

	public func loadInfoBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		infoBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: [])
		if (infoBuffer == nil) { return (Int32(1)) }
		return Int32(0)
	}

	public func loadObjectsBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		objectsBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: [])
		if (objectsBuffer == nil) { return (Int32(1)) }
		return Int32(0)
	}

	public func loadMaterialsBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
		materialsBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: [])
		if (materialsBuffer == nil) { print("mtl: materialsBuffer is nil"); return (Int32(1)) }
		return Int32(0)
	}

	public func loadLightsBuffer(ptr: UnsafeRawPointer, len: Int32) -> Int32 {
    	lightsBuffer = device.makeBuffer(bytes: ptr, length: Int(len), options: [])
    	if (lightsBuffer == nil) { return (Int32(1)) }
    	return Int32(0)
    }

}
