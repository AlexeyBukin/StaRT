/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:25:33 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 20:31:06 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				rt_init(t_rt **rt_dest)
{
	t_rt		*rt;

	if (rt_dest == NULL)
		return (rt_err("rt is NULL pointer"));
	rt = (t_rt*)malloc(sizeof(t_rt));
	if (rt == NULL)
		return (rt_err("rt malloc fail"));
	if (gpu_init(&(rt->gpu)))
		return (rt_err("gpu_init() fail"));
	if (scn_init(&((rt)->scene)))
		return (rt_err("scn_init() fail"));
	*rt_dest = rt;
	return (0);
}

int				rt_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
//	gpu_deinit(rt->gpu);
	scn_deinit(rt->scene);
	ft_free(rt);
	return (0);
}
