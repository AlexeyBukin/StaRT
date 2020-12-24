/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:03:18 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

# define MTL_SHADER_LIST "src/mtl/mtl_shader_list.txt"

int				gpu_init(t_gpu **gpu_dest)
{
	t_gpu		*gpu;
	char		*shader_list;
	char		*lib_source_str;

	if ((gpu = ft_malloc(sizeof(t_gpu))) == NULL)
		return (rt_err("gpu_init(): malloc fail"));
	if ((gpu->dev.mtl = mtl_init()) == NULL)
		return (rt_err("gpu_init(): metal_init() fail"));
	if ((shader_list = ft_read_file(MTL_SHADER_LIST)) == NULL)
		return (rt_err("gpu_init(): cannot read shader list file"));
	if (ft_read_files(&lib_source_str, shader_list))
	{
		ft_free(shader_list);
		return (rt_err("gpu_init(): cannot read shader files"));
	}
	if (mtl_lib_load_source(gpu->dev.mtl, lib_source_str))
	{
		ft_free(shader_list);
		ft_free(lib_source_str);
		return (rt_err("gpu_init(): load_lib() fail"));
	}
	ft_free(shader_list);
	ft_free(lib_source_str);
	if (txr_init_default(&(gpu->render_result), ft_strdup("render_result")))
		return (rt_err("gpu_init(): cannot malloc render_result texture"));
	gpu->render_result->height = 720;
	gpu->render_result->width = 1280;
	gpu->render_result->stride = fio_png_stride((int)gpu->render_result->width * 4);
	gpu->render_result->type = TXR_RGBA_8;
	*gpu_dest = gpu;
	return (0);
}

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_WINDOWS)

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
