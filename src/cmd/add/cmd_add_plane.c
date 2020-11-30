/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:44:38 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 19:45:07 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			init_plane_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (rt_err("Criticall err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	if (cmd_set_plane_default(rt, parser))
		return (rt_err("Given a NULL pointer"));
	return (0);
}

static t_msg		cmd_parse_plane_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "cmd_add_plane(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_add_error(parser, "cmd_add_plane(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_add_error(parser, "cmd_add_plane: bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_add_error(parser, "cmd_add_plane: bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (cmd_add_error(parser, "cmd_add_plane: bad syntax material"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

t_msg           cmd_add_plane(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_plane(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("plane");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_plane(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_plane(): bad name"));
	if (init_plane_parser(rt, parser))
		return (msg_err("cmd_add_plane(): critical malloc error"));
	return (cmd_parse_plane_flags(rt, parser));
}
