//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static int			cylinder_set_length(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-l"))
	{
		parser->cur += ft_strlen("-l");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cylinder.length))
			return (-1);
	}
	return (0);
}

static int			cylinder_set_radius(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cylinder.radius))
			return (-1);
	}
	return (0);
}

int					cmd_set_cylinder_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->container == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cylinder_default(): was given a NULL pointer"));
	parser->container->shape.cylinder.radius = 1.0;
	parser->container->shape.cylinder.length = 1.0;
	parser->object->visible = TRUE;
	parser->object->content.container.shape_type = SHP_CYLINDER;
	parser->object->type = OBJ_CONTAINER;
	parser->material = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME);
	parser->texture = scn_get_txr_by_name(rt->scene, DEFAULT_TEXTURE_NAME);
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg				cmd_set_cylinder_read(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax"));
		if (cylinder_set_radius(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax rad"));
		if (cylinder_set_length(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax length"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax material"));
		if (cmd_set_obj_name(rt, parser) < 0)
			return (cmd_set_error(parser, "cmd_set_cylinder(): bad syntax name"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg				cmd_set_cylinder(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_camera(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_cone(): critical malloc error"));
	return (cmd_set_cylinder_read(rt, parser, dest));
}
