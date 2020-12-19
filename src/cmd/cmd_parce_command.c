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

t_msg			cmd_parse_command(t_rt *rt, t_parser *parser)
{
	char		*str;

	(void)rt;
	if (parser == NULL || parser->source == NULL || parser->cur == NULL)
		return (msg_err("Given NULL pointer in cmd_parce_commands"));
	cmd_read_space(&parser->cur);
	str = parser->cur;
	if (ft_str_next_is(str, "add"))
		return (cmd_add(rt, parser));
	if (ft_str_next_is(str, "set"))
		return (cmd_set(rt, parser));
	if (ft_str_next_is(str, "render"))
		return (cmd_render(rt, parser));
	if (ft_str_next_is(str, "rm"))
		return (cmd_rm(rt, parser));
	if (ft_str_next_is(str, "ls"))
		return (cmd_ls(rt, parser));
	if (ft_str_next_is(str, "vfx"))
		return (cmd_vfx(rt, parser));
	return (msg_warn("Syntax error: Unknown keyword"));
}
