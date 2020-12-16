/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:38:04 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

int				gpu_buffer_load(t_gpu *gpu)
{
	if (gpu == NULL)
		return (rt_err("gpu is NULL pointer"));
	if (mtl_buffer_load_info(gpu->dev.mtl, &(gpu->info), sizeof(t_gpu_info)))
		return (rt_err("cannot load info buffer"));
	if (mtl_buffer_load_objects(gpu->dev.mtl, gpu->obj_buf,
		(int)(sizeof(t_gpu_obj) * gpu->info.obj_num)))
		return (rt_err("cannot load objects buffer"));
	if (mtl_buffer_load_materials(gpu->dev.mtl, gpu->mat_buf,
		(int)(sizeof(t_gpu_mat) * gpu->info.mat_num)))
		return (rt_err("cannot load materials buffer"));
	if (mtl_buffer_load_lights(gpu->dev.mtl, gpu->lgt_buf,
		(int)(sizeof(t_gpu_light) * gpu->info.lgt_num)))
		return (rt_err("cannot load lights buffer"));
	// TODO segfault here
	return (0);
}

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_WINDOWS)

// int				gpu_buffer_load(t_rt *rt)
// {
// 	(void)rt;
// 	return (rt_err("Vulkan not supported"));
// }

#else

int				gpu_buffer_load(t_rt *rt)
{
	(void)rt;
	return (rt_err("gpu_buffer_load() fail"));
}

#endif
