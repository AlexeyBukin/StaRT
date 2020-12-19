/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_kernel_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:04:58 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

# define MTL_MAIN_KERNEL "trace_mod_ggx"

int				gpu_kernel_run(t_gpu *gpu)
{
	size_t				tmp_len;
	unsigned char		*tmp_prt;
	int					target_index;

	if (gpu == NULL)
		return (rt_err("gpu is NULL pointer"));
	target_index = mtl_texture_create_target(gpu->dev.mtl, gpu->render_result->width, gpu->render_result->height);
	if (target_index != 0)
		return (rt_err("kernel_run(): gpu config error"));
	if (mtl_kernel_run(gpu->dev.mtl, MTL_MAIN_KERNEL, target_index))
		return (rt_err("kernel_run() fail"));
	ft_free(gpu->render_result->content);
	tmp_prt = mtl_texture_get_ptr_target(gpu->dev.mtl, target_index);
	tmp_len = gpu->render_result->width * gpu->render_result->height * 4;
	if ((gpu->render_result->content = ft_memdup(tmp_prt, tmp_len)) == NULL)
		return (rt_err("kernel_run(): cannot init texture"));
	return (0);
}

#elif defined(PLATFORM_LINUX) || defined(PPLATFORM_WINDOWS)

int				gpu_kernel_run(t_rt *rt)
{
	(void)rt;
	return (rt_err("Vulkan not supported"));
}

#else

int				gpu_kernel_run(t_rt *rt)
{
	(void)rt;
	return (rt_err("gpu_kernel_run fail"));
}

#endif
