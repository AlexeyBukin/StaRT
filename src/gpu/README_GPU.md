# Gpu module manual

Depending on defined `PLATFORM_XXX` constant gpu module calls appropriate functions from different gpu backends

For example if `PLATFORM_MACOS` is defined `gpu_xxx` calls will trigger `mtl` functions

All gpu calls return int with error if not `0`

## List of main gpu calls
1) `gpu_init(t_rt *rt)` - inits subsystem components, should be called first
2) `gpu_buffer_load(t_rt *rt)` - loads all available buffers into CPU/GPU shared memory
3) `gpu_kernel_run(t_rt *rt)` - runs main kernel (temporary)
