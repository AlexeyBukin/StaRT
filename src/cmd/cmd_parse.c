/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 15:45:16 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/


/*
** work with string as single command, so need to manage it in one move
**when we get word we try to:
1) find out is it command ( else unknown command quit)
1.1) extra funcs for each command for better err managment
2) find out is it arg (if args is invalid - quit err invalid args)
3) find out is it flags (ignore invalid flags)
4) check out values associated with flags is it valid (if not - set default vals)
*/

int		get_one_word(t_word *param, char* str)
{
	int		i;
	int		j;
	// char	*str;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	j = 0;
	param->w_ptr = str + sizeof(char) * i;
	while (str[i] != ' ' && str[i] != '\0')
	{
		// next_word.w_ptr[i - j] = str[i];
		i++;
		j++;
	}
	param->l = j;
	return (1);
	// return (next_word);
}

int			parse_cmd_line(t_rt *rt, const char* str)
{
	(void)rt;
	t_word	params[MAX_PARAMS];
	char	*pstr;
	int		i = 0;

	pstr = (char *)str;
	while (i < MAX_PARAMS && get_one_word(&params[i], pstr) != 0)
	{
		pstr = params[i].w_ptr + params[i].l;
//		write(1, params[i].w_ptr, params[i].l);
//		write(1, "\n", 1);
		i++;
	}
	if (*pstr != '\0')
	{
		return (-1);
	}
	while (i < MAX_PARAMS)
	{
		params[i].l = 0;
		i++;
	}
	return (validate_all_components(rt, (t_word *)params));
}

t_msg		srv_parse_str(t_srv *srv, const char* request)
{
	t_msg	msg;
	msg.status = MSG_NONE;
	if (request == NULL)
		return ((t_msg){MSG_ERROR, "request is NULL pointer"});
	if (ft_strcmp(request, "exit") == 0)
	{
		msg.str = ft_strdup("Closing connection. Have a nice day :) lol\n");
		msg.status = MSG_EXIT;
	}
	else if (ft_strcmp(request, "shutdown") == 0)
	{
		msg.str = ft_strdup("Shutting down...\n");
		msg.status = MSG_SHUT;
	}
	else
	{
		// if (parse_cmd_line(srv->rt, request) != -1)
		// 	;//OK
		parse_cmd_line(srv->rt, request);
		msg.str = ft_strdup(request);
		msg.status = MSG_OK;
	}
	return (msg);
}
