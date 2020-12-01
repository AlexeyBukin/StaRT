//
// Created by Hugor Chau on 11/30/20.
//

#include "rt.h"

int 			init_light_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_LIGHT))
		return (rt_err("init_light_parser(): Critical err malloc"));
	parser->transform = &parser->object->transform;
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg			cmd_parse_read_light(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "add_light(): bad syntax"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax group"));
		if (cmd_light_set_intensity(parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax intensity"));
		if (cmd_light_set_type(parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax type"));
		if (cmd_light_set_color(parser) < 0)
			return (cmd_add_error(parser, "add_light(): bad syntax color"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

t_msg           cmd_add_light(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_light(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("light");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_light(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_light(): bad name"));
	if (init_light_parser(rt, parser))
		return (msg_err("cmd_add_light(): critical malloc error"));
	return (cmd_parse_read_light(rt, parser));
}
