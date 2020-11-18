/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:48:58 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:14:59 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO lock mutex on gui operations
//TODO unlock mutex after gui operations

int				main(int ac, char **av)
{
	t_rt				*rt;

	(void)ac;
	(void)av;
	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	{
//		if (srv_init(rt))
//			return (rt_error("Cannot init server", 0));
//		{
//			if (gui_init(rt))
//				return (rt_error("Cannot init GUI", 0));
//			if (gui_loop(rt, ac, av))
//				return (rt_error("Main loop quit in unexpected manner", 0));
//			if (gui_deinit(rt))
//				return (rt_error("Cannot deinit GUI", 0));
//		}
//		if (srv_deinit(rt))
//			return (rt_error("Cannot deinit server", 0));
	}
//
//	t_mat		*test1;
//	mat_init(&test1, ft_strdup("test1"));
//
//	scn_add_mat(rt->scene, test1);
//	scn_add_mat(rt->scene, test1);
//	scn_remove_by_name_mat(rt->scene, test1->name);
//	scn_remove_by_name_mat(rt->scene, test1->name);
//	scn_add_mat(rt->scene, test1);
//	scn_remove_by_name_mat(rt->scene, test1->name);

	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}
