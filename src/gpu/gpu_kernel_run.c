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
 	if (gpu == NULL)
 		return (rt_err("gpu is NULL pointer"));
 	// if (render_result == NULL)
 	// 	return (rt_err("render_result is NULL pointer"));
	 // gpu->render_result->index was 0
 	if (mtl_kernel_run(gpu->dev.mtl, MTL_MAIN_KERNEL, 0))
 		return (rt_err("kernel_run() fail"));
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
