
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
