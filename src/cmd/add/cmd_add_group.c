/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			init_group_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_GROUP))
		return (rt_err("Critical err malloc"));
	parser->transform = &parser->object->transform;
	if (cmd_set_group_default(rt, parser))
		return (rt_err("Given a NULL pointer"));
	return (0);
}

static t_msg		cmd_parse_group_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, ""
			"cmd_parse_group_flags(): bad syntax or unknown flag"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_add_error(parser, ""
			"cmd_parse_group_flags(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_add_error(parser, ""
			"cmd_parse_group_flags(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_add_error(parser, ""
			"cmd_parse_group_flags(): bad syntax group"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

t_msg				cmd_add_group(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_group(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("group");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_group(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_group(): bad name"));
	if (init_group_parser(rt, parser))
		return (msg_err("cmd_add_group(): critical malloc error"));
	return (cmd_parse_group_flags(rt, parser));
}
