//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static int			check_default_names(t_parser *parser)
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

t_msg		cmd_set(t_rt *rt, t_parser *parser)
{
	if (parser == NULL)
		return(msg_warn("Given NULL pointer in cmd_set()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("Bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_set_obj(): bad name"));
	if (check_default_names(parser))
		return (msg_warn("cmd_set_obj(): can\'t modify default object"));
	return (cmd_set_obj(rt, parser));
}
