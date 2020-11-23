//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

//1) `-v` - visibility. Should be valid string - "true" or "false"
//1) `-n` - name. Should be valid string - name
//1) `-p` - position. Should be valid vector
//1) `-a` - axis. Should be valid matrix 3x3
//1) `-m` - material. Should be valid string - name of material
//1) `-g` - group. Should be valid string - name of group

t_msg		cmd_set_visibility(t_parser *parser)
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
			return (msg_err("cmd_set_visibility(): Bad syntax"));
	}
	return (msg_oks("Oks"));
}

t_msg			cmd_set_name(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-n"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (msg_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(parser->name)))
			return (msg_err("cmd_add_sphere(): bad name"));
	}
	return (msg_oks("Oks"));
}

t_msg		cmd_set_material(t_parser *parser)//find material please!
{
	char		*material_name;

	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		if (cmd_read_space_req(&parser->cur))
			return (msg_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(material_name)))
			return (msg_err("cmd_add_sphere(): bad name"));
	}
	return (msg_oks("Oks"));
}

t_msg		cmd_set_group(t_parser *parser)//find group please!
{
	char		*group_name;

	if (ft_str_next_is(parser->cur, "-g"))
	{
		parser->cur += ft_strlen("-g");
		if (cmd_read_space_req(&parser->cur))
			return (msg_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(group_name)))
			return (msg_err("cmd_add_sphere(): bad name"));
	}
	return (msg_oks("Oks"));
}
