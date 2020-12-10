/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_default_names(t_parser *parser)
{
	if (ft_strequ(parser->name, DEFAULT_GROUP_NAME))
		return (rt_err("cmd_set(): can\'t modify default group"));
	if (ft_strequ(parser->name, DEFAULT_MATERIAL_NAME))
		return (rt_err("cmd_set(): can\'t modify default material"));
	if (ft_strequ(parser->name, DEFAULT_CAMERA_NAME))
		return (rt_err("cmd_set(): can\'t modify default camera"));
	if (ft_strequ(parser->name, DEFAULT_TEXTURE_NAME))
		return (rt_err("cmd_set(): can\'t modify default texture"));
	return (0);
}

static void		cmd_rm_read_force_flag(t_parser *parser, int *rm_force)
{
	char		*str;

	if (*rm_force == 1)
		return ;
	str = parser->cur;
	cmd_read_space(&str);
	if (ft_str_next_is(str, "-r"))
	{
		str += ft_strlen("-r");
		*rm_force = 1;
		parser->cur = str;
	}
}

int				cmd_read_rm(t_parser *parser, int *rm_force)
{
	*rm_force = 0;
	parser->cur += ft_strlen("rm");
	cmd_rm_read_force_flag(parser, rm_force);
	if (cmd_read_space_req(&parser->cur))
		return (rt_err("bad syntax"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (rt_err("bad name string"));
	cmd_rm_read_force_flag(parser, rm_force);
	cmd_read_space(&parser->cur);
	if (*parser->cur)
	{
		cmd_rm_error(parser, "cmd_rm(): invalid name");
		return (rt_err("cmd_rm(): invalid syntax"));
	}
	return (0);
}

t_msg			cmd_rm(t_rt *rt, t_parser *parser)
{
	int		rm_force;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL ptr in cmd_rm"));
	if (cmd_read_rm(parser, &rm_force))
		return (msg_warn("cmd_rm(): invalid syntax or name"));
	if (check_default_names(parser))
		return (cmd_rm_error(parser, "cmd_rm(): can\'t delete default object"));
	return (cmd_rm_by_name(rt, parser, rm_force));
}
