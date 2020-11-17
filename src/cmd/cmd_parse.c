/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 11:05:57 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/

/*
** work with string as single command, so need to manage it in one move
** when we get word we try to:
** 1) find out is it command ( else unknown command quit)
** 1.1) extra funcs for each command for better err managment
** 2) find out is it arg (if args is invalid - quit err invalid args)
** 3) find out is it flags (ignore invalid flags)
** 4) check out values associated with flags is it valid
**		(if not - set default vals)
*/

t_msg				cmd_parse_type_name(char **source, t_parse_help *helper)
{
	int				ecode;

	if (scn == NULL || source == NULL || helper == NULL)
		return (msg_err("Given pointer is NULL"));
	if ((ecode = cmd_parse_switch(source, helper)))
	{
		if (ecode < 0)
			return (msg_err("Cannot parse first argument"));
		return (msg_warn("Cannot parse first argument"));
	}
	if ((ecode = cmd_read_space_req(source)))
	{
		if (ecode < 0)
			return (msg_err("Cannot read space"));
		return (msg_warn("Cannot read space"));
	}
	if ((ecode = cmd_read_string(source, &(helper->name))))
	{
		if (ecode < 0)
			return (msg_err("Cannot read space"));
		return (msg_warn("Cannot read space"));
	}
	return (msg_oks("Parsed component type"));
}

t_msg					cmd_parse_line(t_rt *rt, char *source)
{
	static t_parse_fw	arr[KW_CMD_NUM] = {
		(t_parse_fw){&cmd_add, KW_CMD_ADD},
		// (t_parse_fw){&cmd_ls, KW_CMD_LS},
		// (t_parse_fw){&cmd_rm, KW_CMD_RM},
		(t_parse_fw){&cmd_set, KW_CMD_SET}
	};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, KW_CMD_NUM));
}
