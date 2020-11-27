/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parce_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:15:32 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 21:39:59 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg           cmd_parse_command(t_rt *rt, t_parser *parser)
{
    char        *str;

	(void )rt;
    if (parser == NULL || parser->source == NULL || parser->cur == NULL)
        return (msg_err("Given NULL pointer in cmd_parce_commands"));
	cmd_read_space(&parser->cur);
    str = parser->cur;
	if (ft_str_next_is(str, "add"))
    {
        parser->cur += ft_strlen("add");
		return (cmd_add(rt, parser));
    }
     else if (ft_str_next_is(str, "set"))
     {
         parser->cur += ft_strlen("set");
         return (cmd_set(rt, parser));
     }
	else if (ft_str_next_is(str, "render"))
	{
		parser->cur += ft_strlen("render");
		return (msg_warn("WERE IS RENDER PUT IT IN HERE"));
	}
     //render
    else if (ft_str_next_is(str, "rm"))
    {
        parser->cur += ft_strlen("rm");
        return (cmd_rm(rt, parser));
    }
	else if (ft_str_next_is(str, "ls"))
	{
		parser->cur += ft_strlen("ls");
		if (scn_print(rt->scene))
			return (msg_warn("cmd_parse_command(): couldn\'t print objects"));
		return (msg_oks("It\'s for debug only"));
	}
    // else if (ft_str_next_is(str, "ls"))
    // {
    //     parser->cur += ft_strlen("ls");
    //     return (cmd_parse_ls());
    // }
    return (msg_warn("Syntax error: Unknown keyword"));
}
