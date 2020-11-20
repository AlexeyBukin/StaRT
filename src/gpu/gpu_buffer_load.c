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

// int				gpu_buffer_load(t_rt *rt)
// {
// 	t_scn		*scene;

// 	if (rt == NULL)
// 		return (rt_err("rt is NULL pointer"));
// 	if ((scene = rt->scene) == NULL)
// 		return (rt_err("scene is NULL pointer"));
// 	if (mtl_buffer_load_scene(rt->gpu.mtl, scene, sizeof(t_scn)))
// 		return (rt_err("cannot load scene buffer"));
// 	if (mtl_buffer_load_objects(rt->gpu.mtl, scene->objects, sizeof(t_obj) * scene->objects_num))
// 		return (rt_err("cannot load objects buffer"));
// 	if (mtl_buffer_load_materials(rt->gpu.mtl, scene->materials, sizeof(t_mat) * scene->materials_num))
// 		return (rt_err("cannot load materials buffer"));
// 	return (0);
// }

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
