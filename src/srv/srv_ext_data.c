/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:14:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 05:11:14 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define SRV_STR_ERR_MLK "Server malloc() error."
#define SRV_STR_ERR_PARSE "Server parsing line error."
#define SRV_STR_ERR_READ "Server read() error."
#define SRV_STR_SHUT "Connection is closed, shutting down..."
#define SRV_STR_CLOSE "Connection is closed, server is running..."

int			srv_ext_client_get_data(t_srv *srv)
{
	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (srv->has_client)
	{
		srv->pfd.fd = srv->socket_client_fd;
		srv->pfd.events = POLLIN | POLLHUP | POLLRDNORM;
		srv->pfd.revents = 0;
		if (poll(&(srv->pfd), 1, 0) > 0)
		{
			srv->client_recv = recv(srv->socket_client_fd,
	srv->client_buff, sizeof(srv->client_buff) - 1, MSG_PEEK | MSG_DONTWAIT);
			if (srv->client_recv == 0)
				return (srv_ext_client_disconnect(srv));
			else if (srv->client_recv < 0)
			{
				if (errno == ECONNRESET)
					return (srv_ext_client_disconnect(srv));
				srv_ext_client_disconnect(srv);
				return (rt_err("Server error on recv()"));
			}
			else if (srv_ext_client_update_str(srv))
				return (rt_err("Cannot update client str"));
		}
	}
	return (0);
}

int			srv_ext_client_update_str_error(t_srv *srv, int rc)
{
	if (rc < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
		ft_printf("Errno is %d\n", errno);
		ft_printf("%s\n", SRV_STR_ERR_READ" "SRV_STR_CLOSE);
		return (1);
	}
	return (0);
}

int			srv_ext_client_update_str(t_srv *srv)
{
	int			rc;
	char		*str;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	while ((rc = recv(srv->socket_client_fd, srv->client_buff,
		sizeof(srv->client_buff) - 1, MSG_DONTWAIT)) > 0)
	{
		srv->client_buff[rc] = '\0';
		srv->client_str_size += rc;
		if ((str = (char *)ft_memalloc(srv->client_str_size + 1)) == NULL)
		{
			send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
			srv_ext_client_disconnect(srv);
			return (rt_err(SRV_STR_ERR_MLK" "SRV_STR_SHUT));
		}
		ft_strcpy(str, srv->client_str);
		ft_strcat(str, srv->client_buff);
		ft_free(srv->client_str);
		srv->client_str = str;
	}
	if (srv_ext_client_update_str_error(srv, rc))
		return (srv_ext_client_disconnect(srv));
	return (0);
}

int			srv_ext_client_parse(t_srv *srv)
{
	int					status;
	unsigned long		line_begin;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (srv->has_client && srv->client_str_size > srv->client_str_old_size)
	{
		line_begin = 0;
		if (srv_ext_client_str_parse(srv, &line_begin))
			return (rt_err(SRV_STR_ERR_PARSE" "SRV_STR_SHUT));
		status = srv->response.status;
		if (status == MSG_EXIT || status == MSG_SHUT)
		{
			return (srv_ext_client_disconnect(srv));
		}
		else
		{
			if (srv_ext_client_parse_helper(srv, line_begin))
				return (rt_err("Cannot update client string"));
		}
	}
	return (0);
}

/*
** update client_str so it has no '\n' anymore
*/

int			srv_ext_client_parse_helper(t_srv *srv, unsigned long line_begin)
{
	char				*tmp;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	tmp = ft_strdup(srv->client_str + line_begin);
	free(srv->client_str);
	if ((srv->client_str = tmp) == NULL)
	{
		send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
		close(srv->socket_client_fd);
		return (rt_error(SRV_STR_ERR_MLK" "SRV_STR_SHUT, MSG_ERROR));
	}
	srv->client_str_old_size = ft_strlen(srv->client_str);
	srv->client_str_size = srv->client_str_old_size;
	return (0);
}
