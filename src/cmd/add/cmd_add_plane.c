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

static t_msg			init_plane_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (msg_err("Criticall err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	if (cmd_set_plane_default(rt, parser))
		return (msg_warn("Given a NULL pointer"));
	return (msg_oks("ok"));
}

static t_msg	cmd_parse_plane_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_plane(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("plane_parse_flags(): bad syntax in transform"));
		if (cmd_set_visibility(parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_grp(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax group"));
		if (cmd_set_material(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax material"));
	}
	parser->object->content.container.material = parser->material;
//	parser->object->content.container.texture = parser->texture;//?? where to put?
	return (msg_oks("it works!"));
}

t_msg           cmd_add_plane(t_rt *rt, t_parser *parser)
{
	if (parser == NULL)
		return(msg_err("cmd_add_plane(): given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_plane(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_plane(): bad name"));
	init_plane_parser(rt, parser);
	return (cmd_parse_plane_flags(rt, parser));
}
