/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_gtk_tree_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/08 17:23:41 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					gpu_render(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (gpu_buffer_materials_init(rt->gpu, rt->scene))
		return (rt_err("Cannot init materials buffer"));
	rt->gpu->info.camera.pos = vec3_zero();
	rt->gpu->info.camera.rot_axis = mat3x3_identity();
	rt->gpu->info.camera.fov = (t_vec2){90, 50};
	rt->gpu->info.camera.id = 0;
	if (gpu_buffer_materials_init(rt->gpu, rt->scene))
		return (rt_err("Cannot init materials buffer"));
	if (gpu_buffer_objects_init(rt->gpu, rt->scene))
		return (rt_err("Cannot init objects buffer"));
	if (gpu_buffer_lights_init(rt->gpu, rt->scene))
		return (rt_err("Cannot init lights buffer"));
	if (gpu_buffer_load(rt->gpu))
		return (rt_err("Cannot load buffers to GPU"));
	if (gpu_kernel_run(rt->gpu))
		return (rt_err("Cannot run kernel"));
	return (0);
}
