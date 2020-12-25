/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:56:52 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:01:33 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		srv_prepare(t_srv **server)
{
	if (server == NULL)
		return (rt_err("srv_prepare(): malloc error"));
	if ((*server = ft_memalloc(sizeof(t_srv))) == NULL)
		return (rt_err("srv_init(): malloc returned NULL pointer"));
	(*server)->should_exit = 0;
	(*server)->response = (t_msg){MSG_NONE, NULL};
	(*server)->client_str = NULL;
	(*server)->client_line = NULL;
	(*server)->server_line = NULL;
	(*server)->client_str_size = 0;
	(*server)->client_str_old_size = 0;
	return (0);
}

static int		srv_init_external_part(t_srv *server)
{
	int			can_do;

	can_do = 1;
	if ((server->socket_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (rt_err("could not create TCP listening socket"));
	if ((server->socket_flags = fcntl(server->socket_listen_fd, F_GETFL)) == -1)
		return (rt_err("could not get flags on TCP listening socket"));
	if (fcntl(
			server->socket_listen_fd, F_SETFL,
			server->socket_flags | O_NONBLOCK) == -1)
		return (rt_err("could not set "
		"TCP listening socket to be non-blocking"));
	server->sock_addr.sin_family = AF_INET;
	server->sock_addr.sin_port = htons(SRV_PORT);
	server->sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(
			server->socket_listen_fd,
			(struct sockaddr *)&(server->sock_addr),
			sizeof(server->sock_addr)) == -1)
		return (rt_err("could not bind socket"));
	if (listen(server->socket_listen_fd, 1) == -1)
		return (rt_err("could not set socket to listen"));
	setsockopt(server->socket_listen_fd,
			SOL_SOCKET, SO_REUSEADDR, &can_do, sizeof(int));
	return (0);
}

/*
**	int flags = guard(fcntl(listen_socket_fd, F_GETFL),
** 		"could not get flags on TCP listening socket");
**	guard(fcntl(listen_socket_fd, F_SETFL, flags | O_NONBLOCK),
** 		"could not set TCP listening socket to be non-blocking");
**	struct sockaddr_in addr;
**
**	guard(bind(listen_socket_fd, (struct sockaddr *) &addr,
** 		sizeof(addr)), "could not bind");
**	guard(listen(listen_socket_fd, 1), "could not listen");
*/

int				srv_init(t_rt *rt)
{
	t_srv		*server;

	if (rt == NULL)
		return (rt_err("srv_init(): rt is NULL pointer"));
	if (srv_prepare(&server))
		return (rt_err("srv_init(): malloc returned NULL pointer"));
	if (srv_init_external_part(server))
	{
		ft_free(server);
		return (rt_err("srv_init(): fail"));
	}
	server->rt = rt;
	rt->server = server;
	rt->server_thread = g_thread_try_new(
										"StaRT_server",
										srv_loop,
										(gpointer)rt,
										NULL);
	return (0);
}
