/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_request.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:31:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/01 17:13:15 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Blocking function
*/

#include "rt.h"

int msleep(long msec);

int		srv_request(t_rt *rt, char *str)
{
	int 		code;
	t_srv		*server;

	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if ((server = rt->server) == NULL)
		return (rt_err("server is NULL pointer"));
	while (server->request.status != MSG_NONE)
		msleep(10);
	if (server->response.status != MSG_NONE)
		return (rt_err("server is drunk"));
	server->request.str = str;
	server->request.status = MSG_ACTIVE;
	while (server->response.status == MSG_NONE)
		msleep(10);
	code = server->response.status;
	if (code != MSG_OK && code != MSG_EXIT)
	{
		server->request.status = MSG_ERROR;
		return (rt_err("srv_request(): bad response status code."));
	}
	str = ft_strdup(server->response.str);
	server->request.status = MSG_OK;

	//TODO set 'gtk progress string' to str
	//here it should also set 'gtk progress string' to str
	return (0);
}
