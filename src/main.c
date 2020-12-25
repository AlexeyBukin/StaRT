/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:48:58 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/03 18:28:51 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				main(int ac, char **av)
{
	t_rt				*rt;

	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	{
		if (srv_init(rt))
			return (rt_error("Cannot init server", 0));
		{
			if (gui_init(rt))
				return (rt_error("Cannot init GUI", 0));
			if (gui_loop(rt, ac, av))
				return (rt_error("Main loop quit in unexpected manner", 0));
			if (gui_deinit(rt))
				return (rt_error("Cannot deinit GUI", 0));
		}
		if (srv_deinit(rt))
			return (rt_error("Cannot deinit server", 0));
	}
	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}
