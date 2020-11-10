/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:56:52 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:22:09 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO unbind/close all sockets, fds and stuff

int				srv_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (rt->server == NULL)
		return (rt_err("rt->server is NULL pointer"));
	rt->server->should_exit = 1;
	rt_warn("srv_deinit(): joining server thread");
	g_thread_join(rt->server_thread);
	rt_warn("srv_deinit(): join success");
	return (0);
}
