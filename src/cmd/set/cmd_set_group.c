#include "rt.h"

int				cmd_set_group_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cone_default(): was given a NULL pointer"));
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->object->visible = TRUE;
	parser->object->type = OBJ_GROUP;
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg				cmd_set_group_params(t_rt *rt, t_parser *parser)
{
//	cmd_set_group_default(parser);
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
		if (cmd_set_name(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
	}
	return (msg_oks("it works!"));
}
