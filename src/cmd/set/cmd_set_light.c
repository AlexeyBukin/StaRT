//
// Created by Hugor Chau on 11/30/20.
//

#include "rt.h"

t_msg				cmd_set_light_read(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, "add_light(): bad syntax"));
		if (cmd_read_transform_part(parser))
			return (cmd_set_error(parser, "add_light(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser))
			return (cmd_set_error(parser, "add_light(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser))
			return (cmd_set_error(parser, "add_light(): bad syntax group"));
		if (cmd_light_set_intensity(parser))
			return (cmd_set_error(parser, "add_light(): bad syntax intensity"));
		if (cmd_light_set_type(parser))
			return (cmd_set_error(parser, "add_light(): bad syntax type"));
		if (cmd_light_set_color(parser))
			return (cmd_set_error(parser, "add_light(): bad syntax color"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg		cmd_set_light(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL || dest == NULL)
		return (msg_err("cmd_set_ligth(): given NULL pointer"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_cone(): critical malloc error"));
	return (cmd_set_light_read(rt, parser, dest));
}