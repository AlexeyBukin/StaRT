/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 09:15:38 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO change
** gpointer as (void *)
*/

//#define SRV_OK     0
//#define SRV_EXIT   1
//#define SRV_ERROR -1

void		srv_quit_gtk_app(t_rt *rt);

void*				srv_loop(void* rt_pointer)
{
	char			error;
	t_srv			*server;

	if ((t_rt*)rt_pointer == NULL)
		return (NULL);
	if ((server = ((t_rt*)rt_pointer)->server) == NULL)
	{
		rt_err("srv_loop(): server is NULL");
		return (NULL);
	}

	while (1)
	{
		// process internal request
//		if (server->request.status == MSG_ACTIVE)
//		{
//			rt_warn("srv_loop(): got request");
//			server->response = srv_parse_str(server, server->request.str);
//			while (server->request.status == MSG_ACTIVE)
//				msleep(10);
//			if (server->response.status == MSG_ERROR || server->request.status == MSG_ERROR)
//			{
//				return (null(rt_err("srv_loop(): server request error")));
//			}
//			if (server->response.status == MSG_SHUT)
//			{
//				return (null(rt_warn("srv_loop(): shutting server down...")));
//			}
//			server->response = (t_msg){MSG_NONE, NULL};
//			server->request = (t_msg){MSG_NONE, NULL};
//		}
		// process external request
		{
			if ((error = srv_ext_client_process(rt_pointer)) < 0)
			{
				// notify gtk about error
				rt_err("srv_loop(): srv_ext_client_process() returned error code");
				break ;
			}
			else
			{
				if (server->response.status == MSG_SHUT)
				{
					rt_warn("Shutting down...");
					srv_quit_gtk_app((t_rt*)rt_pointer);
//					//TODO server deinit than exit()
//					t_rt *rt = (t_rt*)rt_pointer;
//					g_application_quit(G_APPLICATION(rt->app));
					break ;
//					exit(0);
				}
				server->response = (t_msg){MSG_NONE, NULL};
				server->request = (t_msg){MSG_NONE, NULL};
			}
		}
//		rt_warn("srv_loop(): sleeping");
		msleep(10);
	}
	rt_warn("srv_loop(): ending server thread");
	return (NULL);
}


static gboolean
srv_g_application_quit(gpointer void_app)
{
	g_application_quit(G_APPLICATION(void_app));
	return G_SOURCE_REMOVE;
}

void		srv_quit_gtk_app(t_rt *rt)
{
	GSource *source;

	if (rt == NULL)
		return ;
	source = g_idle_source_new();
	g_source_set_callback(source, srv_g_application_quit, rt->app, NULL);
	g_source_attach(source, rt->context);
}

