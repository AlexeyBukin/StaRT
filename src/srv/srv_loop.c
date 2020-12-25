/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:25:36 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			srv_shut_down(void *rt_pointer, t_srv *server)
{
	if ((t_rt*)rt_pointer == NULL || server == NULL)
		return (1);
	if (server->response.status == MSG_SHUT)
	{
		rt_warn("Shutting down...");
		srv_quit_gtk_app((t_rt*)rt_pointer);
		return (1);
	}
	server->response = (t_msg){MSG_NONE, NULL};
	return (0);
}

/*
**	rt_warn("srv_loop(): sleeping");
*/

void				*srv_loop(void *rt_pointer)
{
	t_srv			*server;

	if ((t_rt*)rt_pointer == NULL)
		return (NULL);
	if ((server = ((t_rt*)rt_pointer)->server) == NULL)
		return (null(rt_err("srv_loop(): server is NULL")));
	while (1)
	{
		if (server->should_exit)
			break ;
		if ((srv_ext_client_process((t_rt*)rt_pointer)) < 0)
		{
			rt_err("srv_loop(): srv_ext_client_process() returned error code");
			srv_quit_gtk_app((t_rt*)rt_pointer);
			break ;
		}
		else if (srv_shut_down(rt_pointer, server))
			break ;
		msleep(10);
	}
	rt_warn("srv_loop(): ending server thread");
	return (NULL);
}
