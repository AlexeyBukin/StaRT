/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:14:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/02 16:57:54 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char welcome_msg[] = "Server is ready. Type 'exit' to close connection.\n";
char error_msg[]   = "Some error caused server to close connection. Press 'Enter' to continue.\n";
char busy_msg[]    = "Server is currently used by another session/user. Try later.\n";

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
	return (srv_ext_client_str_process(srv));

	return (0);
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
			send(srv->socket_client_fd, welcome_msg, sizeof(welcome_msg), 0);
//			rt_warn("Got an external connection; writing welcome message.\n");
		}
	}
	else
	{
		refuse_fd = accept(srv->socket_listen_fd, NULL, NULL);
		send(refuse_fd, busy_msg, sizeof(busy_msg), 0);
		close (refuse_fd);
	}
	return (0);
}

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
			ft_printf("\nclient_recv is %d\n\n", srv->client_recv);
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
			send(srv->socket_client_fd, error_msg, sizeof(error_msg), 0);
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
		send(srv->socket_client_fd, error_msg, sizeof(error_msg), 0);
		ft_printf("Errno is %d\n", errno);
		ft_printf("%s\n", "Server read() error. Connection is closed, server is running...");
		return (srv_ext_client_disconnect(srv));
	}
	return (0);
}

int				srv_ext_client_str_process(t_srv *srv)
{
	char				*tmp;
	t_msg				srv_msg;
	unsigned long		i;
	unsigned long		line_begin;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (srv->has_client && srv->client_str_size > srv->client_str_old_size)
	{
		ft_printf("got up here, wow\n");
//		int count = 0;
		i = srv->client_str_old_size;
		line_begin = 0;
//		recode = MSG_OK;
		srv_msg.status = MSG_NONE;
		srv_msg.str = NULL;
		while (i < srv->client_str_size)
		{
			if (srv->client_str[i] == '\n')
			{
//				//TODO deleteme
//				count ++;
//				printf("Serving newline number %d\n", count);

				srv->client_line = ft_strndup(srv->client_str + line_begin, i - line_begin);
				line_begin = i + 1;

				ft_printf("got up here, wow\n");

				srv_msg = srv_parse_str(srv, srv->client_line);

				free(srv->client_line);
				srv->client_line = NULL;

				if (srv_msg.status == MSG_ERROR || srv_msg.str == NULL)
				{
					// some serious error occured, must close
					send(srv->socket_client_fd, error_msg, sizeof(error_msg), 0);
					close(srv->socket_client_fd);
					return (rt_err("Server process line error. Connection is closed, shutting down..."));
				}

//				printf("This newline is '%s'\n\n", server_line);
				send(srv->socket_client_fd, srv_msg.str, ft_strlen(srv_msg.str), 0);
//				free(srv_msg.str);

				if (srv_msg.status == MSG_EXIT)
					break ;
				free(srv_msg.str);
			}
			i++;
		}

		if (srv_msg.status == MSG_EXIT)
		{
			return (srv_ext_client_disconnect(srv));
		}
		else
		{
			// update client_str so it has no '\n' anymore
			tmp = ft_strdup(srv->client_str + line_begin);
			free(srv->client_str);
			srv->client_str = tmp;
			if (srv->client_str == NULL)
			{
				send(srv->socket_client_fd, error_msg, sizeof(error_msg), 0);
				close(srv->socket_client_fd);
				return (rt_error("Server malloc() error. Connection is closed, shutting down...", MSG_ERROR));
			}
			srv->client_str_old_size = ft_strlen(srv->client_str);
			srv->client_str_size = srv->client_str_old_size;
//			printf("Client str left is '%s'\n", client_str);
		}
	}
	return (0);
}
