/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/04 21:06:44 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

#define MTL_LIB_SRC "src/gpu/mtl/shaders/rt_mtl___kernel.metal"
#define MTL_WIDTH	1280
#define MTL_HEIGHT	720

int				gpu_init(t_rt *rt)
{
	t_texture	*render_result;

	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->gpu.mtl = mtl_init();
	if (rt->gpu.mtl == NULL)
		return (rt_err("gpu_init(): metal_init() fail"));
	if (mtl_lib_load_source(rt->gpu.mtl, ft_read_file(MTL_LIB_SRC) ))
		return (rt_err("gpu_init(): load_lib() fail"));
	if ((render_result = (t_texture*)ft_memalloc(sizeof(t_texture))) == NULL)
		return (rt_err("gpu_init(): ft_memalloc() fail"));
	if ((render_result->index = mtl_texture_create(rt->gpu.mtl, MTL_WIDTH, MTL_HEIGHT)) < 0)
		return (rt_err("gpu_init(): texture_create() fail"));
	render_result->width = MTL_WIDTH;
	render_result->height = MTL_HEIGHT;
	if ((render_result->stride = mtl_texture_get_stride(rt->gpu.mtl, render_result->index)) <= 0)
		return (rt_err("gpu_init(): get_stride() fail"));

	//TODO delete debug
	ft_printf("index is %d\nstride is %d\n", render_result->index, render_result->stride);

	if ((render_result->data = mtl_texture_get_ptr(rt->gpu.mtl, render_result->index)) == NULL)
		return (rt_err("gpu_init(): get_ptr() fail"));
	rt->render_result = render_result;

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
