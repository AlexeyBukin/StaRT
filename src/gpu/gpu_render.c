/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:36:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				gpu_render_simple(t_gpu *gpu)
{
	t_txr		*rgba_res;
	t_txr		*rgb;
	t_size2		render_size;

	if (gpu == NULL)
		return (rt_err("Given pointer is NULL"));
	render_size.x = 160;
	render_size.y = 90;
//	if (txr_init(&(gpu->render_result), ft_strdup("render_texture"), render_size))
//		return (rt_err("Cannot init render texture"));
	if (gpu_buffer_objects_init(gpu))
		return (rt_err("Cannot init objects buffer"));
//	if (gpu_buffer_materials_init(gpu))
//		return (rt_err("Cannot init materials buffer"));
//	if (gpu_buffer_textures_init(gpu))
//		return (rt_err("Cannot init textures buffer"));
	if (gpu_buffer_load(gpu))
		return (rt_err("Cannot load buffers"));
	int target_index0 = mtl_texture_create_target(gpu->dev.mtl, render_size.x, render_size.y);
	res = mtl_kernel_run(gpu->dev.mtl, "trace_mod_ggx", target_index0);
	if (res != 0)
		return (rt_err("Cannot run kernel"));

//	unsigned char  *texture_rbga_target =
//	unsigned char  *texture_rbg_target = mtl_texture_get_ptr_target(gpu->dev.mtl, target_index0);

//  returned texture is rgba
//  returned texture made with mmap(), not malloc() : we have to copy it

	if (txr_init_default(&rgba_res, ft_strdup("rgba_res")))
		return (rt_err("Cannot init texture"));
	rgba_res->width = render_size.x;
	rgba_res->height = render_size.y;
	rgba_res->stride = rgba_res->width * 4;
	rgba_res->content =  mtl_texture_get_ptr_target(gpu->dev.mtl, target_index0);

	if (txr_rgba_to_rgb(rgba_res, &rgb))
		return (rt_err("Cannot convert rgba to rgb"));

	rgba_res->content = NULL;
	txr_deinit(rgba_res);

	gpu->render_result = rgb;

//	mtl_buffer_free(); // TODO add to mtl
 	return (0);
}

int				gpu_render(t_rt *rt)
{
	return (gpu_render_simple(rt->gpu));
}
