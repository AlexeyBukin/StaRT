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

int				srv_init(t_rt *rt)
{
	t_srv		*server;

	if (rt == NULL)
		return (rt_err("srv_init(): rt is NULL pointer"));
	if ((server = ft_memalloc(sizeof(t_srv))) == NULL)
		return (rt_err("srv_init(): malloc returned NULL pointer"));
	server->should_exit = 0;
	server->response = (t_msg){MSG_NONE, NULL};
	server->client_str = NULL;
	server->client_line = NULL;
	server->server_line = NULL;
	server->client_str_size = 0;
	server->client_str_old_size = 0;

	// external part
	if ((server->socket_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (rt_err("could not create TCP listening socket"));
	if ((server->socket_flags = fcntl(server->socket_listen_fd, F_GETFL)) == -1)
		return (rt_err("could not get flags on TCP listening socket"));
	if (fcntl(server->socket_listen_fd, F_SETFL, server->socket_flags | O_NONBLOCK) == -1)
		return (rt_err("could not set TCP listening socket to be non-blocking"));
	server->sock_addr.sin_family = AF_INET;
	server->sock_addr.sin_port = htons(SRV_PORT);
	server->sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server->socket_listen_fd, (struct sockaddr *) &(server->sock_addr), sizeof(server->sock_addr)) == -1)
		return (rt_err("could not bind socket"));
	if (listen(server->socket_listen_fd, 1) == -1)
		return (rt_err("could not set socket to listen"));
//


//	int flags = guard(fcntl(listen_socket_fd, F_GETFL), "could not get flags on TCP listening socket");
//	guard(fcntl(listen_socket_fd, F_SETFL, flags | O_NONBLOCK), "could not set TCP listening socket to be non-blocking");
//	struct sockaddr_in addr;
//
//	guard(bind(listen_socket_fd, (struct sockaddr *) &addr, sizeof(addr)), "could not bind");
//	guard(listen(listen_socket_fd, 1), "could not listen");
	server->rt = rt;
	rt->server = server;

	rt->server_thread = g_thread_new(NULL, srv_loop, (gpointer)rt);
	return (0);
}
