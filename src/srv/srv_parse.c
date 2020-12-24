/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:09:44 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 21:51:57 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg		srv_parse_str(t_srv *srv, const char *request)
{
	t_msg	msg;

	msg.status = MSG_NONE;
	if (request == NULL)
		return ((t_msg){MSG_ERROR, "request is NULL pointer"});
	if (ft_strcmp(request, "exit") == 0)
	{
		msg.str = SRV_EXIT;
		msg.status = MSG_EXIT;
	}
	else if (ft_strcmp(request, "shutdown") == 0)
	{
		msg.str = SRV_SHUT;
		msg.status = MSG_SHUT;
	}
	else if (ft_strcmp(request, "") == 0)
	{
		msg.str = ft_strdup("");
		msg.status = MSG_OK;
	}
	else if (ft_strncmp(request, "#", 1) == 0)
	{
		msg.str = ft_strdup("");
		msg.status = MSG_OK;
	}
	else
	{
		//TODO lock mutex
//		ft_printf("parsing line \'%s\'\n", srv->client_line);
		// t_rt *rt = srv->rt;

		// g_mutex_lock(rt->mutex);
		//TODO on!
		ft_printf("incoming line \'%s\'\n", srv->client_line);
		msg = cmd_parse_line(srv->rt, (char *)request);
		// g_mutex_unlock(rt->mutex);
		ft_printf("done parsing line \'%s\'\n", srv->client_line);
		//TODO unlock mutex
	}
	return (msg);
}
