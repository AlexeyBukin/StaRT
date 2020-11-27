
#include "rt.h"

static int			cone_set_radius(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cone.radius))
			return (-1);
	}
	return (0);
}

static int			cone_set_length(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-l"))
	{
		parser->cur += ft_strlen("-l");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cone.length))
			return (-1);
	}
	return (0);
}

static t_msg	cmd_parse_cone_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cone_parse_flags(): bad syntax1"));
		if (cone_set_radius(parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax in rad"));
		if (cone_set_length(parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax in rad"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (msg_warn("cone_parse_flags(): bad syntax material"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

static int			init_cone_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (rt_err("init_cone_parser(): Critical err malloc"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	if (cmd_set_cone_default(rt, parser))
		return (rt_err("Given a NULL pointer"));
	return (0);
}

t_msg           cmd_add_cone(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_cone(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("cone");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_cone(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_cone(): bad name"));
	if (init_cone_parser(rt, parser))
		return (msg_err("cmd_add_cone(): critical malloc error"));
	return (cmd_parse_cone_flags(rt, parser));
}
