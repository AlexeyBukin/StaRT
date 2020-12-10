/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:36:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

//#define MTL_LIB_SRC "src/mtl/shaders/rt_mtl___kernel.metal"
#define MTL_LIB_SRC "src/mtl/shaders/metal_struct.metal src/mtl/shaders/metal_shader.metal src/mtl/shaders/rt_trace_mod_ggx.metal"
#define MTL_WIDTH	1280
#define MTL_HEIGHT	720

int				gpu_init(t_gpu **gpu_dest)
{
	t_gpu		*gpu;
	char		*lib_source_str;
//	t_txr		*render_result;

	if (gpu_dest == NULL)
		return (rt_err("Given pointer is NULL"));

	if ((gpu = ft_malloc(sizeof(t_gpu))) == NULL)
		return (rt_err("gpu_init(): malloc fail"));
	if ((gpu->dev.mtl = mtl_init()) == NULL)
		return (rt_err("gpu_init(): metal_init() fail"));
	if (ft_read_files(&lib_source_str, MTL_LIB_SRC))
		return (rt_err("gpu_init(): cannot read shader files"));
	if (mtl_lib_load_source(gpu->dev.mtl, lib_source_str))
		return (rt_err("gpu_init(): load_lib() fail"));
	free(lib_source_str);
//	if ((render_result = (t_texture*)ft_memalloc(sizeof(t_texture))) == NULL)
//		return (rt_err("gpu_init(): ft_memalloc() fail"));
//	if ((render_result->index = mtl_texture_create(rt->gpu.mtl, MTL_WIDTH, MTL_HEIGHT)) < 0)
//		return (rt_err("gpu_init(): texture_create() fail"));
//	render_result->width = MTL_WIDTH;
//	render_result->height = MTL_HEIGHT;
//	if ((render_result->stride = mtl_texture_get_stride(rt->gpu.mtl, render_result->index)) <= 0)
//		return (rt_err("gpu_init(): get_stride() fail"));

// 	//TODO delete debug
// 	ft_printf("index is %d\nstride is %d\n", render_result->index, render_result->stride);

// 	if ((render_result->data = mtl_texture_get_ptr(rt->gpu.mtl, render_result->index)) == NULL)
// 		return (rt_err("gpu_init(): get_ptr() fail"));
// 	rt->render_result = render_result;
	*gpu_dest = gpu;
 	return (0);
 }

#elif defined(PLATFORM_LINUX) || defined(PPLATFORM_WINDOWS)

int				gpu_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->gpu.vlk = vlk_init();
	if (rt->gpu.vlk == NULL)
		return (rt_err("gpu_init() fail"));
	return (0);
}

#else

int				gpu_init(t_rt *rt)
{
	(void)rt;
	return (rt_err("gpu_init() fail"));
}

#endif
