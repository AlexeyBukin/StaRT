/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:14:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/02 20:23:27 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				srv_ext_client_get_data(t_srv *srv)
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
			srv->client_recv = recv(srv->socket_client_fd, srv->client_buff, sizeof(srv->client_buff) - 1, MSG_PEEK | MSG_DONTWAIT);
/* poll() tells that socket changed; recv() tell there is no data on socket -> connection has been closed by client with no error */
//			ft_printf("\nclient_recv is %d\n\n", srv->client_recv);
			if (srv->client_recv == 0)
				return (srv_ext_client_disconnect(srv));
			if (srv->client_recv > 0)
				if (srv_ext_client_update_str(srv))
					return (rt_err("Cannot update client str"));
			if (srv->client_recv < 0)
			{
				//recv() error occured
				if (errno == ECONNRESET)
				{
					//client failed
					//but we should stand
					return (srv_ext_client_disconnect(srv));
				}
				else
				{
					// we failed
					srv_ext_client_disconnect(srv);
					return (rt_err("Server error on recv()"));
				}
			}
		}
	}
	return (0);
}

int				srv_ext_client_update_str(t_srv *srv)
{
	int			rc;
	char		*new_str;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	// read all available data into string 'client_str'
	// mark that new data available
	// client_str_size = client_old_size + n;
	while ((rc = read(srv->socket_client_fd, srv->client_buff, sizeof(srv->client_buff) - 1)) > 0)
	{
		srv->client_buff[rc] = '\0';
		srv->client_str_size += rc;
		if ((new_str = (char *)ft_memalloc(srv->client_str_size + 1)) == NULL)
		{
			send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
			srv_ext_client_disconnect(srv);
			return (rt_err("Server malloc() error. Connection is closed, shutting down..."));
		}
		ft_strcpy(new_str, srv->client_str);
		ft_strcat(new_str, srv->client_buff);
		ft_free(srv->client_str);
		srv->client_str = new_str;
	}
	if (rc < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		//error on read from fd
		//try to send error_msg and close connection
		send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
		ft_printf("Errno is %d\n", errno);
		ft_printf("%s\n", "Server read() error. Connection is closed, server is running...");
		return (srv_ext_client_disconnect(srv));
	}
	return (0);
}

int				srv_ext_client_parse(t_srv *srv)
{
	unsigned long		line_begin;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (srv->has_client && srv->client_str_size > srv->client_str_old_size)
	{
		line_begin = 0;
		if (srv_ext_client_str_parse(srv, &line_begin))
			return (rt_err("Server parsing line error. Connection is closed, shutting down..."));
		if (srv->response.status == MSG_EXIT || srv->response.status == MSG_SHUT)
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

int				srv_ext_client_parse_helper(t_srv *srv, unsigned long line_begin)
{
	char				*tmp;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));

	// update client_str so it has no '\n' anymore
	tmp = ft_strdup(srv->client_str + line_begin);
	free(srv->client_str);
	if ((srv->client_str = tmp) == NULL)
	{
		send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
		close(srv->socket_client_fd);
		return (rt_error("Server malloc() error. Connection is closed, shutting down...", MSG_ERROR));
	}
	srv->client_str_old_size = ft_strlen(srv->client_str);
	srv->client_str_size = srv->client_str_old_size;
	return (0);
}

int				srv_ext_client_str_parse(t_srv *srv, unsigned long *line_begin)
{
	unsigned long		i;

	if (srv == NULL || line_begin == NULL)
		return (rt_err("argument is NULL pointer"));
	i = srv->client_str_old_size;
	ft_free(srv->response.str);
	srv->response = (t_msg){MSG_NONE, NULL};
	while (i < srv->client_str_size)
	{
		if (srv->client_str[i] == '\n')
		{
			srv->client_line = ft_strndup(srv->client_str + *line_begin, i - *line_begin);
			*line_begin = i + 1;

			srv->response = srv_parse_str(srv, srv->client_line);

			ft_free(srv->client_line);
			srv->client_line = NULL;

			if (srv->response.status == MSG_ERROR || srv->response.str == NULL)
			{
				// some serious error occured, must close
				send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
				close(srv->socket_client_fd);
				return (rt_err("Server process line error. Connection is closed, shutting down..."));
			}
			send(srv->socket_client_fd, srv->response.str, ft_strlen(srv->response.str), 0);
			ft_free(srv->response.str);
			srv->response.str = NULL;

			if (srv->response.status == MSG_EXIT || srv->response.status == MSG_SHUT)
				break ;
		}
		i++;
	}
	return (0);
}
