/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
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

int					cmd_set_sphere_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->container == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cone_default(): was given a NULL pointer"));
	parser->object->content.container.shape_type = SHP_SPHERE;
	parser->container->shape.sphere.radius = 1.0;
	parser->object->visible = TRUE;
	parser->object->type = OBJ_CONTAINER;
	parser->material = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME);
	parser->texture = scn_get_txr_by_name(rt->scene, DEFAULT_TEXTURE_NAME);
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg				cmd_set_sphere_read(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax transform"));
		if (sphere_set_radius(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax rad"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax material"));
		if (cmd_set_obj_name(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_sphere(): bad syntax name"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg				cmd_set_sphere(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_camera(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_cone(): critical malloc error"));
	return (cmd_set_sphere_read(rt, parser, dest));
}
