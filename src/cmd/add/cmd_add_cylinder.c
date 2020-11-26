#include "rt.h"

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

static int			init_cylinder_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (rt_err("init_cylinder_parser(): critical malloc error"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	if (cmd_set_cylinder_default(rt, parser))
		return (rt_err("init_cylinder_parser(): critical malloc error"));
	return (0);
}

static t_msg	cmd_parse_cylinder_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_cylinder(): bad syntax1"));
		if (cylinder_set_radius(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in rad"));
		if (cylinder_set_length(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in rad"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in transform"));
		if (cmd_set_visibility(parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_grp(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax group"));
		if (cmd_set_mat(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax material"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

t_msg           cmd_add_cylinder(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_cylinder(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("cylinder");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_cylinder(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_cylinder(): bad name"));
	if (init_cylinder_parser(rt, parser))
		return (msg_err("Criticall err malloc"));
	return (cmd_parse_cylinder_flags(rt, parser));
}
