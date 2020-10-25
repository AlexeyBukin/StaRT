/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:48:58 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 14:40:27 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				rt_init(t_rt **rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	*rt = (t_rt*)ft_memalloc(sizeof(t_rt));
	if (*rt == NULL)
		return (rt_err("rt malloc fail"));
	if (gpu_init(*rt))
		return (rt_err("gpu_init() fail"));
	return (0);
}

int				rt_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	free(rt);
	return (0);
}

int				main(int ac, char **av)
{
	t_rt				*rt;

	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	if (gui_init(rt))
		return (rt_error("Cannot init GUI", 0));
	if (gui_loop(rt, ac, av))
		return (rt_error("Main loop quit in unexpected manner", 0));
	if (gui_deinit(rt))
		return (rt_error("Cannot deinit GUI", 0));
	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}