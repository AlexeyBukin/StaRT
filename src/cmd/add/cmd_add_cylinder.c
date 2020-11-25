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

static t_msg			init_cylinder_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (msg_err("Criticall err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	if (cmd_set_cylinder_default(rt, parser))
		return (msg_err("Given a NULL pointer"));
	return (msg_oks("ok"));
}

static t_msg	cmd_parse_cylinder_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
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
		if (cmd_set_material(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax material"));
	}
	parser->object->content.container.material = parser->material;
	parser->object->name = parser->name;
//	parser->object->content.container.texture = parser->texture;//?? where to put?
	scn_add_to_group(rt->scene, parser->group, parser->object);
	return (msg_oks("it works!"));
}

t_msg           cmd_add_cylinder(t_rt *rt, t_parser *parser)
{
	if (parser == NULL)
		return(msg_err("cmd_add_cylinder(): given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_cylinder(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_cylinder(): bad name"));
	init_cylinder_parser(rt, parser);
	return (cmd_parse_cylinder_flags(rt, parser));
}
