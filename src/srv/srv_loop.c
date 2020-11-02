/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/02 16:37:30 by kcharla          ###   ########.fr       */
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
		if (server->request.status == MSG_ACTIVE)
		{
			rt_warn("srv_loop(): got request");
			server->response = srv_parse_str(server, server->request.str);
			while (server->request.status == MSG_ACTIVE)
				msleep(10);
			if (server->response.status == MSG_ERROR || server->request.status == MSG_ERROR)
			{
				return (null(rt_err("srv_loop(): server request error")));
			}
			if (server->response.status == MSG_EXIT)
			{
				return (null(rt_warn("srv_loop(): shutting server down...")));
			}
		}
		if ((error = srv_ext_client_process(rt_pointer)) < 0)
		{
			// notify gtk about error
			rt_err("srv_loop(): srv_ext_client_process() returned error code");
			break ;
		}
//		rt_warn("srv_loop(): sleeping");
		msleep(10);
	}
	rt_warn("srv_loop(): ending server thread");
	return (NULL);
}

//int				srv_parse_str(const char* request, char **response)
//{
//	if (request == NULL || response == NULL)
//		return (MSG_ERROR);
//	if (ft_strcmp(request, "exit") == 0)
//	{
//		*response = ft_strdup("Shutting down server...");
//		return (MSG_EXIT);
//	}
//	return (MSG_OK);
//}
