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

//	t_cam		*here;
//	t_cam		*same_name;
//
//	cam_init(&here, "random_string");
//	cam_init(&same_name, "random_string");
//	if (cam_add(rt->scene, here))
//		ft_putstr("Ok\n");
//	if (cam_add(rt->scene, here))
//		ft_putstr("Ok\n");
//	if (cam_add(rt->scene, same_name))
//		ft_putstr("Ok\n");
//	if (cam_add(rt->scene, here))
//		ft_putstr("Ok\n");
//	ft_printf("%d\n", rt->scene->cameras_num);
//	size_t 	i;
//	i = 0;
//	while (i < rt->scene->cameras_num)
//	{
//		ft_printf("cameras_num = %s\n", rt->scene->cameras[i]->name);
//		i++;
//	}
//	if (scn_name_check(rt->scene, DEFAULT_MATERIAL_NAME))
//		ft_putendl(scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME)->name);
	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}