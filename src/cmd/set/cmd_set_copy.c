//
// Created by Hugor Chau on 12/1/20.
//

#include "rt.h"

static int				cmd_read_obj_copy(t_rt *rt, t_parser *parser)
{
	char		*tmp_name;
	t_obj		*tmp_obj;

	if (ft_str_next_is(parser->cur, "-o"))
	{
		parser->cur += ft_strlen("-o");
		cmd_read_space(&parser->cur);
		if (cmd_read_string(&parser->cur, &tmp_name))
			return (-1);
		tmp_obj = scn_get_obj_by_name(rt->scene, tmp_name);
		if (tmp_obj == NULL)
		{
			ft_free(tmp_name);
			return (-1);
		}
		ft_free(tmp_name);
		parser->object->content.copy = tmp_obj;
		return (0);
	}
	return (0);
}

t_msg					cmd_set_copy_params(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax group"));
		if (cmd_set_obj_name(rt, parser) < 0)
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax name"));
		if (cmd_read_obj_copy(rt, parser))
			return (cmd_set_error(parser, "cmd_set_copy(): bad syntax object link"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg		cmd_set_copy(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL || dest == NULL)
		return (msg_err("cmd_set_copy(): given NULL pointer"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_copy(): critical malloc error"));
	if (dest->parent == NULL)
		return (msg_warn("cmd_set_copy(): can\'t modify main copy. Stop."));
	return (cmd_set_copy_params(rt, parser, dest));
//	return (msg_oks("oks"));
}