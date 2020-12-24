/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:47:19 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 09:54:14 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRV_TYPES_H
# define SRV_TYPES_H

# include <fcntl.h>
# include <netinet/in.h>
# include <errno.h>
# include <memory.h>
# include <poll.h>
# include <time.h>

typedef struct		s_msg
{
	int				status;
	char			*str;
}					t_msg;

/*
** only server can write to response
*/

typedef struct		s_srv
{
	struct s_rt			*rt;
	int					should_exit;
	t_msg				response;
	int					socket_listen_fd;
	int					socket_flags;
	struct sockaddr_in	sock_addr;
	int					has_client;
	int					socket_client_fd;
	struct pollfd		pfd;
	int					client_recv;
	char				client_buff[256];
	char				*client_str;
	char				*client_line;
	char				*server_line;
	unsigned long		client_str_size;
	unsigned long		client_str_old_size;
}					t_srv;

#endif
