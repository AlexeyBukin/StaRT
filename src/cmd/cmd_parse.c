/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/03 22:55:50 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/

t_msg		cmd_parse(t_rt *rt, const char* request)
{
	t_msg	msg;
	(void)rt;
	msg.status = MSG_NONE;
	if (request == NULL)
		return ((t_msg){MSG_ERROR, "request is NULL pointer"});
	if (ft_strcmp(request, "exit") == 0)
	{
		msg.str = ft_strdup("Closing connection. Have a nice day :)\n");
		msg.status = MSG_EXIT;
	}
	else if (ft_strcmp(request, "shutdown") == 0)
	{
		msg.str = ft_strdup("Shutting down...\n");
		msg.status = MSG_SHUT;
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
