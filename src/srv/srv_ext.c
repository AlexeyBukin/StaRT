/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:14:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/01 20:10:58 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char welcome_msg[] = "Server is ready. Type 'exit' to close connection.\n";
char error_msg[]   = "Some error caused server to close connection. Press 'Enter' to continue.\n";
char busy_msg[]    = "Server is currently used by another session/user. Try later.\n";

int		srv_ext_client_process(t_rt *rt)
{
	int			refuse_fd;
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




	//
//	// proceed data that changed
//	// *** blocking part ***
//	if (has_client && client_str_size > client_str_old_size)
//	{
//		int count = 0;
//		unsigned long i = client_str_old_size;
////			unsigned long i = 0;
//		unsigned long line_begin = 0;
//		int recode = RESPONSE_OK;
//		while (i < client_str_size)
//		{
//			if (client_str[i] == '\n')
//			{
//				//TODO deleteme
//				count ++;
//				printf("Serving newline number %d\n", count);
//
//
//				client_line = strndup(client_str + line_begin, i - line_begin);
//				line_begin = i + 1;
//
//				recode = server_process_client_line(client_line, &server_line);
//
//				free(client_line);
//				client_line = NULL;
//
//				if (recode == RESPONSE_ERROR || server_line == NULL)
//				{
//					// some serious error occured, must close
//					send(client_socket_fd, error_msg, sizeof(error_msg), 0);
//					close(client_socket_fd);
//					printf("%s\n", "Server process line error. Connection is closed, shutting down...");
//					exit(1);
//				}
//
//				printf("This newline is '%s'\n\n", server_line);
//				send(client_socket_fd, server_line, strlen(server_line), 0);
//				free(server_line);
//
//				if (recode == RESPONSE_EXIT)
//				{
//					break ;
//				}
//			}
//			i++;
//		}
//
//		if (recode == RESPONSE_EXIT)
//		{
//			has_client = 0;
//			close(client_socket_fd);
//
//			free(client_str);
//			client_str = NULL;
//			client_str_size = 0;
//			client_str_old_size = 0;
//		}
//		else
//		{
//			// update client_str so it has no '\n' anymore
//			char *tmp = strdup(client_str + line_begin);
//			free(client_str);
//			client_str = tmp;
//			if (client_str == NULL){
//				send(client_socket_fd, error_msg, sizeof(error_msg), 0);
//				close(client_socket_fd);
//				printf("%s\n", "Server malloc() error. Connection is closed, shutting down...");
//				exit(1);
//			}
//			client_str_old_size = strlen(client_str);
//			client_str_size = client_str_old_size;
//			printf("Client str left is '%s'\n", client_str);
//		}
//	}

	return (0);
}

int				srv_ext_check_client(t_srv *srv)
{
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
	char		client_buff[256];
	char		*new_str;

	if (srv == NULL)
		return (rt_err("srv is NULL pointer"));
	if (srv->has_client)
	{
//		printf("Getting client info...\n");
//		struct pollfd pfd;
		srv->pfd.fd = client_socket_fd;
		srv->pfd.events = POLLIN | POLLHUP | POLLRDNORM;
		srv->pfd.revents = 0;
		if (poll(&(srv->pfd), 1, 0) > 0)
		{
			srv->client_recv = recv(srv->socket_client_fd, client_buff, sizeof(client_buff) - 1, MSG_PEEK | MSG_DONTWAIT);
			if (srv->client_recv == 0)
			{
				// poll() tells that socket changed
				// recv() tell there is no data on socket
				// that means that connection has been closed by client with no error
				return (srv_ext_client_disconnect(srv));
			}
			else if (client_recv > 0)
			{
				srv_ext_client_update_str(srv);
//				// read all available data into string 'client_str'
//				// mark that new data available
//				// client_str_size = client_old_size + n;
//				while ((client_recv = read(client_socket_fd, client_buff, sizeof(client_buff) - 1)) > 0)
//				{
//					client_buff[client_recv] = '\0';
//					client_str_size += + client_recv;
////						if (client_str != NULL)
////							client_str_old_size += strlen(client_str);
//
//					if ((new_str = (char *)malloc(client_str_size + 1)) == NULL)
//					{
//						send(client_socket_fd, error_msg, sizeof(error_msg), 0);
//						srv_ext_client_disconnect(srv);
//						return (rt_err("Server malloc() error. Connection is closed, shutting down..."));
//					}
//					*new_str = '\0';
//					if (client_str != NULL)
//						new_str = strcpy(new_str, client_str);
//					new_str = ft_strcat(new_str, client_buff);
//					ft_free(client_str);
//					client_str = new_str;
//				}
//				if (client_recv < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
//				{
//					//error on read from fd
//					//try to send error_msg and close connection
//					send(client_socket_fd, error_msg, sizeof(error_msg), 0);
//					ft_printf("Errno is %d\n", errno);
//					ft_printf("%s\n", "Server read() error. Connection is closed, server is running...");
//					return (srv_ext_client_disconnect(srv));
//				}
//				printf("New str is '%s', size is %lu\n", client_str, client_str_size);
			}
			else
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
}

int				srv_ext_client_update_str(t_srv *srv)
{
	// read all available data into string 'client_str'
	// mark that new data available
	// client_str_size = client_old_size + n;
	while ((client_recv = read(client_socket_fd, client_buff, sizeof(client_buff) - 1)) > 0)
	{
		client_buff[client_recv] = '\0';
		client_str_size += + client_recv;
//						if (client_str != NULL)
//							client_str_old_size += strlen(client_str);

		if ((new_str = (char *)malloc(client_str_size + 1)) == NULL)
		{
			send(client_socket_fd, error_msg, sizeof(error_msg), 0);
			srv_ext_client_disconnect(srv);
			return (rt_err("Server malloc() error. Connection is closed, shutting down..."));
		}
		*new_str = '\0';
		if (client_str != NULL)
			new_str = strcpy(new_str, client_str);
		new_str = ft_strcat(new_str, client_buff);
		ft_free(client_str);
		client_str = new_str;
	}
	if (client_recv < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		//error on read from fd
		//try to send error_msg and close connection
		send(client_socket_fd, error_msg, sizeof(error_msg), 0);
		ft_printf("Errno is %d\n", errno);
		ft_printf("%s\n", "Server read() error. Connection is closed, server is running...");
		return (srv_ext_client_disconnect(srv));
	}
}
