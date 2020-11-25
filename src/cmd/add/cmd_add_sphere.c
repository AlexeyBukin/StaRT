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

// -p - pos
// -a - angle

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

static t_msg			init_sphere_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (msg_err("Criticall err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	cmd_set_sphere_default(rt, parser);
	return (msg_oks("ok"));
}

static t_msg	cmd_parse_sphere_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_sphere(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("sphere_parse_flags(): bad syntax in transform"));
		if (sphere_set_radius(parser) < 0)
			return (msg_warn("sphere_parse_flags(): bad syntax in rad"));
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

t_msg           cmd_add_sphere(t_rt *rt, t_parser *parser)
{
	if (parser == NULL)
		return(msg_err("cmd_add_sphere(): given NULL pointer in cmd_add()"));
    if (cmd_read_space_req(&parser->cur))
        return (msg_warn("cmd_add_sphere(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
        return (msg_warn("cmd_add_sphere(): bad name"));
	init_sphere_parser(rt, parser);
	return (cmd_parse_sphere_flags(rt, parser));
}
