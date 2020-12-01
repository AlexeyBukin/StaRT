/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 20:28:13 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

 int				gpu_buffer_load(t_gpu *gpu)
 {
 	if (gpu == NULL)
 		return (rt_err("gpu is NULL pointer"));
 	if (mtl_buffer_load_info(gpu->dev.mtl, &(gpu->info), sizeof(t_scn)))
 		return (rt_err("cannot load info buffer"));
 	if (mtl_buffer_load_objects(gpu->dev.mtl, gpu->obj_buf,
							  (int)(sizeof(t_gpu_obj) * gpu->info.obj_num)))
 		return (rt_err("cannot load objects buffer"));
 	if (mtl_buffer_load_materials(gpu->dev.mtl, gpu->mat_buf,
								(int)(sizeof(t_mat) * gpu->info.mat_num)))
 		return (rt_err("cannot load materials buffer"));
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
