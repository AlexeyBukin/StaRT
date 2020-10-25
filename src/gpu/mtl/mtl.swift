
import Cocoa

import mtl_start

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
public func mtl_lib_load_source_swift(_ smptr: UnsafeRawPointer, _ libsrcptr: UnsafePointer<CChar>) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.loadLibrary(source: String(cString: libsrcptr)))
}

@_cdecl("mtl_texture_add")
public func mtl_texture_add_swift(_ smptr: UnsafeRawPointer, _ width: Int32, _ height: Int32) -> Int32
{
	let sm:StartMTL = _mtl_bridge(ptr:smptr)
	return (sm.addTexture(d: sm.device, w: Int(width), h: Int(height)))
}

@_cdecl("mtl_texture_get_ptr")
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
