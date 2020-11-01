/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/01 17:21:32 by kcharla          ###   ########.fr       */
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
//	char			*response;
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
		// process request
		if (server->request.status == MSG_ACTIVE)
		{
			rt_warn("srv_loop(): got request");
			server->response.status = srv_parse_str(server->request.str, &(server->response.str));
			while (server->request.status == MSG_ACTIVE)
				msleep(10);
			if (server->response.status == MSG_ERROR || server->request.status == MSG_ERROR)
			{
				rt_err("srv_loop(): server request error");
				break ;
			}
			if (server->response.status == MSG_EXIT)
			{
				rt_warn("srv_loop(): shutting server down...");
				break ;
			}
		}
		rt_warn("srv_loop(): sleeping");
		sleep(1);
	}
	rt_warn("srv_loop(): ending server thread");
	return (NULL);
}

int				srv_parse_str(const char* request, char **response)
{
	if (request == NULL || response == NULL)
		return (MSG_ERROR);
	if (ft_strcmp(request, "exit") == 0)
	{
		*response = ft_strdup("Shutting down server...");
		return (MSG_EXIT);
	}
	return (MSG_OK);
}

int				msleep(long msec)
{
	struct timespec ts;
	int res;

	if (msec < 0)
	{
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;

	do {
		res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);

	return res;
}
