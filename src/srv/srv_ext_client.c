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

int		srv_ext_client_nextline(t_srv *srv, size_t i, unsigned long *lb)
{
	srv->client_line = ft_strndup(srv->client_str + *lb, i - *lb);
	*lb = i + 1;
	srv->response = srv_parse_str(srv, srv->client_line);
	ft_strdel(&srv->client_line);
	if (srv->response.status == MSG_ERROR || srv->response.str == NULL)
	{
		if (srv->response.str != NULL)
		{
			send(srv->socket_client_fd, srv->response.str,
				ft_strlen(srv->response.str), 0);
			send(srv->socket_client_fd, "\n", 1, 0);
		}
		send(srv->socket_client_fd, SRV_ERR, ft_strlen(SRV_ERR), 0);
		close(srv->socket_client_fd);
		return (rt_err(SRV_STR_ERR_PARSE" "SRV_STR_SHUT));
	}
	send(srv->socket_client_fd, srv->response.str,
		ft_strlen(srv->response.str), 0);
	send(srv->socket_client_fd, "\n", 1, 0);
	if (srv->response.status == MSG_OK)
		ft_free(srv->response.str);
	srv->response.str = NULL;
	if (srv->response.status == MSG_EXIT || srv->response.status == MSG_SHUT)
		return (1);
	return (0);
}

int		srv_ext_client_str_parse(t_srv *srv, unsigned long *line_begin)
{
	int					res;
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
			res = srv_ext_client_nextline(srv, i, line_begin);
			if (res < 0)
				return (rt_err(SRV_STR_ERR_PARSE" "SRV_STR_SHUT));
			else if (res > 0)
				break ;
		}
		i++;
	}
	return (0);
}
