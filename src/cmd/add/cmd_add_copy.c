
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

t_msg			cmd_read_copy(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "cmd_add_copy(): bad syntax"));
		if (cmd_read_transform_part(parser))
			return (cmd_add_error(parser, "cmd_add_copy(): bad syntax in transform"));
		if (cmd_set_obj_visibility(parser))
			return (cmd_add_error(parser, "cmd_add_copy(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser))
			return (cmd_add_error(parser, "cmd_add_copy(): bad syntax group"));
		if (cmd_read_obj_copy(rt, parser))
			return (cmd_add_error(parser, "cmd_add_copy(): bad syntax group"));
	}
	if (parser->object->content.copy == NULL)
		return (cmd_add_error(parser, "cmd_add_copy(): copy was not linked to any object"));
	return (cmd_add_obj_to_scn(rt, parser));
}

int 			cmd_init_copy_parser(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (rt_err("cmd_init_copy_parser(): given NULL pointer"));
	if (obj_init(&parser->object, parser->name, OBJ_COPY))
		return (rt_err("cmd_init_copy_parser(): can\'t init object"));
	parser->transform = &parser->object->transform;
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg			cmd_add_copy(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_copy(): given NULL pointer"));
	parser->cur += ft_strlen("copy");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_copy(): bad syntax"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (msg_warn("cmd_add_copy(): bad name"));
	if (cmd_init_copy_parser(rt, parser))
		return (msg_err("Criticall err malloc"));
//	free(parser->name);
	return (cmd_read_copy(rt, parser));
}
