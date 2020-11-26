//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

static t_msg			init_group_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_GROUP))
		return (msg_err("Criticall err malloc"));
	parser->transform = &parser->object->transform;
	if (cmd_set_group_default(rt, parser))
		return (msg_warn("Given a NULL pointer"));
	return (msg_oks("ok"));
}

static t_msg	cmd_parse_group_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_group(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("group_parse_flags(): bad syntax in transform"));
		if (cmd_set_visibility(parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_grp(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax group"));
	}
	parser->object->name = parser->name;
	scn_add_to_group(rt->scene, parser->group, parser->object);
	return (msg_oks("it works!"));
}

t_msg           cmd_add_group(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_group(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("group");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_group(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_group(): bad name"));
	init_group_parser(rt, parser);
	return (cmd_parse_group_flags(rt, parser));
}
