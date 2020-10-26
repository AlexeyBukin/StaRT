/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 14:28:11 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(PLATFORM_MACOS)

int				gpu_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->gpu.mtl = mtl_init();
	if (rt->gpu.mtl == NULL)
		return (rt_err("gpu_init() fail"));
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
