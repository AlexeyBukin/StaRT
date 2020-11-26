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

t_msg					cmd_set_group_params(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp;

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
	tmp = scn_get_obj_by_name(rt->scene, parser->object->name);
	ft_memcpy(tmp, parser->object, sizeof(t_obj));
	tmp->name = parser->name;
	if (parser->group != tmp->parent)
		scn_move_obj(rt->scene, parser->group, tmp);
	return (msg_oks("it works!"));
}

t_msg			cmd_set_group(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp;

	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_group(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("group");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_group(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_group(): bad name"));
	if (!(tmp = scn_get_obj_by_name(rt->scene, parser->name)))
		return (msg_warn("cmd_set_group(): couldn\'t find object"));
	if (tmp->type != OBJ_GROUP)
		return (msg_warn("cmd_set_group(): object is not a group"));
	if (!(parser->object = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (msg_err("cmd_set_group(): malloc error"));
	ft_memcpy(parser->object, tmp, sizeof(t_obj));
	parser->name = ft_strdup(tmp->name);
	parser->transform = &parser->object->transform;
	return (cmd_set_group_params(rt, parser));
}