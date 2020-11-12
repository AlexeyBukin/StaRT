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

void*				srv_loop(void* rt_pointer)
{
	char			error;
	t_srv			*server;

	if ((t_rt*)rt_pointer == NULL)
		return (NULL);
	if ((server = ((t_rt*)rt_pointer)->server) == NULL)
		return (null(rt_err("srv_loop(): server is NULL")));
	while (1)
	{
		if (server->should_exit)
			break ;
		if ((error = srv_ext_client_process((t_rt*)rt_pointer)) < 0)
		{
			// notify gtk about error?
			rt_err("srv_loop(): srv_ext_client_process() returned error code");
			srv_quit_gtk_app((t_rt*)rt_pointer);
			break ;
		}
		else
		{
			if (server->response.status == MSG_SHUT)
			{
				rt_warn("Shutting down...");
				srv_quit_gtk_app((t_rt*)rt_pointer);
				break ;
			}
			server->response = (t_msg){MSG_NONE, NULL};
		}
//		rt_warn("srv_loop(): sleeping");
		msleep(10);
	}
	rt_warn("srv_loop(): ending server thread");
	return (NULL);
}
