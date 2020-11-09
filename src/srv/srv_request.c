/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_request.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:31:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 18:08:57 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Blocking function
*/

#include "rt.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
** GUI calls shpuld call this request func
** wait for writing to socket
*/

int		srv_request(t_rt *rt, char *str)
{
	char *server_localhost = "127.0.0.1";
	(void)str;
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;

//	int 		code;
	t_srv		*server;

	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if ((server = rt->server) == NULL)
		return (rt_err("server is NULL pointer"));

	ft_memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SRV_PORT);

	if(inet_pton(AF_INET, server_localhost, &serv_addr.sin_addr)<=0)
	{
		printf("\n inet_pton error occured\n");
		return 1;
	}
	if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	}
	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
	{
		recvBuff[n] = 0;
		if(fputs(recvBuff, stdout) == EOF)
		{
			ft_printf("\n Error : Fputs error\n");
		}
	}

	if(n < 0)
	{
		ft_printf("\n Read error \n");
		return (rt_err("Error in socket"));
	}

	return (0);
}
