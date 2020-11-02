/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:09:44 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/02 16:41:00 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg		srv_parse_str(t_srv *srv, const char* request)
{
	t_msg	msg;
	(void)srv;
//	(void)str;
//	(void)response;
//	return (0);

//	int		recode;
//	char	*res;

	msg.status = MSG_NONE;
	if (request == NULL)
		return ((t_msg){MSG_ERROR, "request is NULL pointer"});
	if (ft_strcmp(request, "exit") == 0)
	{
		msg.str = ft_strdup("Closing connection. Have a nice day :)\n");
		msg.status = MSG_EXIT;
	}
	else
	{
//		printf("str '%s' and '%s' are not the same\n", "exit", cline);
		msg.str = ft_strdup(request);
		msg.status = MSG_OK;
//		return (msg);
//		res = strdup("Unknown command. Try again.\n");
	}
	return (msg);
}
