/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:48:58 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/04 21:57:59 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include "rt.h"

int				main(int ac, char **av)
{
	GThread				*server_thread;
	t_rt				*rt;

	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	if (gui_init(rt))
		return (rt_error("Cannot init GUI", 0));
	// add thread with server
	if (srv_init(rt))
		return (rt_error("Cannot init server", 0));
	server_thread = g_thread_new(NULL, srv_loop, (gpointer)rt);

	if (gui_loop(rt, ac, av))
		return (rt_error("Main loop quit in unexpected manner", 0));
	if (gui_deinit(rt))
		return (rt_error("Cannot deinit GUI", 0));

	// send server 'exit' request
	// join server thread
	srv_shutdown(rt);
	rt_warn("main(): srv_shutdown() success");
	g_thread_join(server_thread);
	rt_warn("main(): join success");

	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}