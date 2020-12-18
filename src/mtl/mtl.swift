
import Cocoa

import mtl_start
import mtl_texture
import mtl_buffer

func _mtl_bridge<T : AnyObject>(obj : T) -> UnsafeRawPointer {
	return UnsafeRawPointer(Unmanaged.passUnretained(obj).toOpaque())
}

func _mtl_bridge_retained<T : AnyObject>(obj : T) -> UnsafeRawPointer {
	return UnsafeRawPointer(Unmanaged.passRetained(obj).toOpaque())
}

func _mtl_bridge<T : AnyObject>(ptr : UnsafeRawPointer) -> T {
	return Unmanaged<T>.fromOpaque(ptr).takeUnretainedValue()
}

func _mtl_bridge_transfer<T : AnyObject>(ptr : UnsafeRawPointer) -> T {
	return Unmanaged<T>.fromOpaque(ptr).takeRetainedValue()
}

@_cdecl("mtl_init")
public func mtl_init_swift() -> UnsafeRawPointer
{
	let sm = StartMTL()
	return (_mtl_bridge_retained(obj:sm))
}

@_cdecl("mtl_lib_load_source")
public func mtl_lib_load_source_swift(_ smptr: UnsafeRawPointer, _ libsrcptr: UnsafePointer<CChar>?) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	guard libsrcptr != nil else { print("mtl: NULL pointer error"); return (Int32(-1)) }
	return (sm.loadLibrary(source: String(cString: libsrcptr!)))
}

/* TEXTURE PART */

@_cdecl("mtl_texture_create_target")
public func mtl_texture_create_swift(_ smptr: UnsafeRawPointer, _ width: Int32, _ height: Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.createTexture(d: sm.device, w: Int(width), h: Int(height)))
}

@_cdecl("mtl_texture_get_ptr_target")
public func mtl_texture_get_ptr_swift(_ smptr: UnsafeRawPointer, _ index: Int32) -> UnsafeMutablePointer<UInt32>?
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.getTexturePointer(index: Int(index)))
}

@_cdecl("mtl_texture_get_width")
public func mtl_texture_get_width_swift(_ smptr: UnsafeRawPointer, _ index: Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.getTextureWidth(index: index))
}

@_cdecl("mtl_texture_get_height")
public func mtl_texture_get_height_swift(_ smptr: UnsafeRawPointer, _ index: Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.getTextureWidth(index: index))
}

@_cdecl("mtl_texture_get_stride")
public func mtl_texture_get_stride_swift(_ smptr: UnsafeRawPointer, _ index: Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.getTextureStride(index: index))
}

@_cdecl("mtl_texture_target_save")
public func mtl_texture_target_save_swift(_ smptr: UnsafeRawPointer, _ index: Int32, _ path: UnsafePointer<CChar>?) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	if (path == nil) { print ("mtl: NULL pointer"); return (Int32(-1)) }
	let pathString = String(cString: path!)
	return (sm.saveTargetTextureAsPNG(index: Int(index), path: pathString))
}

@_cdecl("mtl_texture_resource_rgba8_load")
public func mtl_texture_resource_rgba8_load_swift(_ smptr: UnsafeRawPointer?, _ ptr:UnsafeRawPointer?, _ width:Int32, _ height:Int32 ) -> Int32
{
	if (smptr == nil || ptr == nil) { print ("mtl: NULL pointer"); return (Int32(-1)) }
	if (width <= 0 || height <= 0) { print ("mtl: incorrect arguments"); return (Int32(-1)) }
	let sm:StartMTL = _mtl_bridge(ptr:smptr!)
	return (sm.loadTextureResourceRGBA8(data: ptr!, width: Int(width), height: Int(height)))
}

@_cdecl("mtl_texture_target_rgba8_load")
public func mtl_texture_target_rgba8_load_swift(_ smptr: UnsafeRawPointer?, _ ptr:UnsafeRawPointer?, _ width:Int32, _ height:Int32 ) -> Int32
{
	if (smptr == nil || ptr == nil) { print ("mtl: NULL pointer"); return (Int32(-1)) }
	if (width <= 0 || height <= 0) { print ("mtl: incorrect arguments"); return (Int32(-1)) }
	let sm:StartMTL = _mtl_bridge(ptr:smptr!)
	return (sm.loadTextureTargetRGBA8(data: ptr!, width: Int(width), height: Int(height)))
}


/* BUFFER PART */

@_cdecl("mtl_buffer_load_info")
public func mtl_buffer_load_info_swift(_ smptr: UnsafeRawPointer, _ ptr:UnsafeRawPointer, _ len:Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.loadInfoBuffer(ptr: ptr, len: len))
}

@_cdecl("mtl_buffer_load_objects")
public func mtl_buffer_load_objects_swift(_ smptr: UnsafeRawPointer, _ ptr:UnsafeRawPointer, _ len:Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.loadObjectsBuffer(ptr: ptr, len: len))
}

@_cdecl("mtl_buffer_load_materials")
public func mtl_buffer_load_materials_swift(_ smptr: UnsafeRawPointer, _ ptr:UnsafeRawPointer, _ len:Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.loadMaterialsBuffer(ptr: ptr, len: len))
}

@_cdecl("mtl_buffer_load_lights")
public func mtl_buffer_load_lights_swift(_ smptr: UnsafeRawPointer, _ ptr:UnsafeRawPointer, _ len:Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.loadLightsBuffer(ptr: ptr, len: len))
}

/* KERNEL PART */

@_cdecl("mtl_kernel_run")
public func mtl_kernel_run_swift(_ smptr: UnsafeRawPointer, _ kernel_name: UnsafePointer<CChar>, _ texture_out_index:Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.runStartKernel(name: String(cString: kernel_name), textureID: Int(texture_out_index)))
}