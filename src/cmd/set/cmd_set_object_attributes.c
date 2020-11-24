//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

/*
** `-v` - visibility. Should be valid string - "true" or "false"
** `-n` - name. Should be valid string - name
** `-m` - material. Should be valid string - name of material
** `-g` - group. Should be valid string - name of group
**
*/

int				cmd_set_visibility(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-v"))
	{
		parser->cur += ft_strlen("-v");
		cmd_read_space(&parser->cur);
		if (ft_str_next_is(parser->cur, "true"))
			parser->object->visible = TRUE;
		else if (ft_str_next_is(parser->cur, "false"))
			parser->object->visible = FALSE;
		else
			return (rt_err("cmd_set_visibility(): Bad syntax"));
		return (1);
	}
	return (0);
}

int				cmd_set_name(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-n"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(parser->name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		return (1);
	}
	return (0);
}

int				cmd_set_material(t_parser *parser)//find material please!
{
	char		*material_name;

	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(material_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		return (1);
	}
	return (0);
}

int				cmd_set_group(t_parser *parser)//find group please!
{
	char		*group_name;

	if (ft_str_next_is(parser->cur, "-g"))
	{
		parser->cur += ft_strlen("-g");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(group_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		return (1);
	}
	return (0);
}

int				cmd_set_obj_attributes(t_parser *parser)
{
	int		parsed_flags;

	parsed_flags = 0;
	if ((parsed_flags | cmd_set_visibility(parser)) < 0)
		return (rt_err("cmd_set_obj_attributes: bad syntax"));
	if ((parsed_flags | cmd_set_name(parser)) < 0)
		return (rt_err("cmd_set_obj_attributes: bad syntax"));
	return (parsed_flags);
}
