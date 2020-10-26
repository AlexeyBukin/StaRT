/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 16:59:04 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

# define MTL_MAIN_KERNEL "scene_test"

int				gpu_kernel_run(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (rt->render_result == NULL)
		return (rt_err("render_result is NULL pointer"));
	if (mtl_kernel_run(rt->gpu.mtl, MTL_MAIN_KERNEL, rt->render_result->index))
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

int				gpu_init(t_rt *rt)
{
	(void)rt;
	return (rt_err("gpu_init() fail"));
}

#endif
