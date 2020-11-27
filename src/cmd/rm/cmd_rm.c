#include "rt.h"

static int		check_default_names(t_parser *parser)
{
	if (ft_strequ(parser->name, DEFAULT_GROUP_NAME))
		return (rt_err("cmd_set(): can\'t modify default group"));
	if (ft_strequ(parser->name, DEFAULT_MATERIAL_NAME))
		return (rt_err("cmd_set(): can\'t modify default material"));
	if (ft_strequ(parser->name, DEFAULT_CAMERA_NAME))
		return (rt_err("cmd_set(): can\'t modify default camera"));
	if (ft_strequ(parser->name, DEFAULT_TEXTURE_NAME))
		return (rt_err("cmd_set(): can\'t modify default texture"));
	return (0);
}

static void		cmd_rm_read_force_flag(t_parser *parser, int *rm_force)
{
	char		*str;

	if (*rm_force == 1)
		return ;
	str = parser->cur;
	cmd_read_space(&str);
	if (ft_str_next_is(str, "-r"))
	{
		str += ft_strlen("-r");
		*rm_force = 1;
		parser->cur = str;
	}
}

t_msg           cmd_rm(t_rt *rt, t_parser *parser)
{
	int		rm_force;

	rm_force = 0;
	if (rt == NULL || parser == NULL)
		return (msg_err("NULL ptr in cmd_rm"));
	cmd_rm_read_force_flag(parser, &rm_force);
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("bad syntax"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (msg_warn("bad name string"));
	cmd_rm_read_force_flag(parser, &rm_force);
	cmd_read_space(&parser->cur);
	if (*parser->cur)
		return (msg_warn("cmd_rm(): bad syntax"));
	if (check_default_names(parser))
		return (msg_warn("cmd_rm(): can\'t delete default object"));
	return (cmd_rm_by_name(rt, parser, rm_force));
}
