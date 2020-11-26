//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

/*
** `-v` - visibility. Should be valid string - "true" or "false"
** `-n` - name. Should be valid string - name
** `-m` - material. Should be valid string - name of material
** `-g` - group. Should be valid string - name of group
*/

int				cmd_set_visibility(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-v"))
	{
		parser->cur += ft_strlen("-v");
		cmd_read_space(&parser->cur);
		if (ft_str_next_is(parser->cur, "\"true\""))
		{
			parser->object->visible = TRUE;
			parser->cur += ft_strlen("\"true\"");
		}
		else if (ft_str_next_is(parser->cur, "\"false\""))
		{
			parser->object->visible = FALSE;
			parser->cur += ft_strlen("\"false\"");
		}
		else
			return (rt_err("cmd_set_visibility(): Bad syntax"));
	}
	return (0);
}

int				cmd_set_name(t_rt *rt, t_parser *parser)
{
	char		*tmp;

	(void)rt;
	if (ft_str_next_is(parser->cur, "-n"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &tmp))
			return (rt_err("cmd_add_sphere(): bad name"));
		if (scn_name_check(rt->scene, tmp))
			return (rt_err("cmd_set_name(): name collision"));
		ft_free(parser->name);
		parser->name = tmp;
	}
	return (0);
}

int				cmd_set_mat(t_rt *rt, t_parser *parser)//find material please!
{
	char		*material_name;
	t_mat		*material;

	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(material_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		if ((material = scn_get_mat_by_name(rt->scene, material_name)) == NULL)
			return (rt_err("cmd_add_sphere(): material with given "
				"name does not exist"));
		parser->material = material;
	}
	return (0);
}

int				cmd_set_grp(t_rt *rt, t_parser *parser)//find group please!
{
	char		*group_name;
	t_obj		*group;

	if (ft_str_next_is(parser->cur, "-g"))
	{
		parser->cur += ft_strlen("-g");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(group_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		if ((group = scn_get_obj_by_name(rt->scene, group_name)) == NULL)
			return (rt_err("cmd_add_sphere(): couldn't find group"));
		if (group->type != OBJ_GROUP)
			return (rt_err("cmd_add_sphere(): object with given"
			" name is not a group"));
		parser->group = group;
	}
	return (0);
}
