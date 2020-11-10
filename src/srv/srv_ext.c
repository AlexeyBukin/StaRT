/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:14:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		srv_ext_client_process(t_rt *rt)
{
	t_srv		*srv;

	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if ((srv = rt->server) == NULL)
		return (rt_err("srv is NULL pointer"));

	// check if we have connection to client
	if (srv_ext_client_check(srv))
		return (rt_err("failed to check client"));

	// check if client socket has data and get it
	// non-blocking as well
	if (srv_ext_client_get_data(srv))
		return (rt_err("failed to get client data"));

	// proceed data that changed
	return (srv_ext_client_parse(srv));
}

int				srv_ext_client_check(t_srv *srv)
{
	int			refuse_fd;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (!(srv->has_client))
	{
		if ((srv->socket_client_fd = accept(srv->socket_listen_fd, NULL, NULL)) == -1)
		{
			if (errno != EWOULDBLOCK)
				return (rt_err("Cannot accept connection"));
//			else
//				rt_warn("No pending connections right now.\n");
		}
		else
		{
			srv->has_client = 1;
			send(srv->socket_client_fd, SRV_HELLO, ft_strlen(SRV_HELLO), 0);
			rt_warn("Got an external connection; writing welcome message.\n");
		}
	}
	else
	{
		refuse_fd = accept(srv->socket_listen_fd, NULL, NULL);
		send(refuse_fd, SRV_BUSY, ft_strlen(SRV_BUSY), 0);
		close (refuse_fd);
	}
	return (0);
}

int				srv_ext_client_disconnect(t_srv *srv)
{
	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));

	srv->has_client = 0;
	close(srv->socket_client_fd);

	ft_free(srv->client_str);
	srv->client_str = NULL;
	srv->client_str_size = 0;
	srv->client_str_old_size = 0;

//	rt_warn("Client disconnected\n");
	return (0);
}
