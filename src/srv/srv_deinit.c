/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_deinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:56:52 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:22:09 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	 TODO unbind/close all sockets, fds and stuff
*/

int				srv_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (rt->server == NULL)
		return (rt_err("rt->server is NULL pointer"));
	rt->server->should_exit = 1;
	rt_warn("srv_deinit(): joining server thread");
	g_thread_join(rt->server_thread);
//	shutdown (rt->server->socket_listen_fd, SHUT_RDWR);
//	close(rt->server->socket_listen_fd);
	ft_free(rt->server);
	rt->server = NULL;
	rt_warn("srv_deinit(): join success");
	return (0);
}
