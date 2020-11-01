/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:56:52 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/31 21:09:02 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				srv_init(t_rt *rt)
{
	t_srv		*server;

	if (rt == NULL)
		return (rt_err("srv_init(): rt is NULL pointer"));
	if ((server = malloc(sizeof(t_srv))) == NULL)
		return (rt_err("srv_init(): malloc returned NULL pointer"));
	server->response.status = MSG_NONE;
	server->response.str = NULL;
	server->request.status = MSG_NONE;
	server->request.str = NULL;
	rt->server = server;
	return (0);
}
