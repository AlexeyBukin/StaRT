/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:41:35 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 21:55:10 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			sphere_set_radius(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.sphere.radius))
			return (-1);
	}
	return (0);
}

static t_msg	cmd_parse_sphere_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "cmd_set_sphere(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_add_error(parser, "sphere_parse_flags(): bad syntax in transform"));
		if (sphere_set_radius(parser) < 0)
			return (cmd_add_error(parser, "sphere_parse_flags(): bad syntax in rad"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_add_error(parser, "cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_add_error(parser, "cmd_set_obj_attributes: bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (cmd_add_error(parser, "cmd_set_obj_attributes: bad syntax material"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

static int			init_sphere_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (rt_err("Criticall err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	return (cmd_set_sphere_default(rt, parser));
}

t_msg           cmd_add_sphere(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_sphere(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("sphere");
    if (cmd_read_space_req(&parser->cur))
        return (msg_warn("cmd_add_sphere(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
        return (msg_warn("cmd_add_sphere(): bad name"));
	if (init_sphere_parser(rt, parser))
		return (msg_err("cmd_add_sphere(): critical malloc error"));
	return (cmd_parse_sphere_flags(rt, parser));
}
