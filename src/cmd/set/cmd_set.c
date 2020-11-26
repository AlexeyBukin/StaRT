//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

t_msg		cmd_set(t_rt *rt, t_parser *parser)
{
	char			*str;

	if (parser == NULL)
		return(msg_warn("Given NULL pointer in cmd_set()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "cone"))
		cmd_switch_condition(rt, parser, cmd_set_cone, "cone");
	else if (ft_str_next_is(str, "plane"))
	{
		parser->cur += ft_strlen("plane");
		return (cmd_set_plane(rt, parser));
	}
	else if (ft_str_next_is(str, "cylinder"))
	{
		parser->cur += ft_strlen("cylinder");
		return (cmd_set_cylinder(rt, parser));
	}
	else if (ft_str_next_is(str, "sphere"))
	{
		parser->cur += ft_strlen("sphere");
		return (cmd_set_sphere(rt, parser));
	}
	else if (ft_str_next_is(str, "group"))
	{
		parser->cur += ft_strlen("group");
		return (cmd_set_group(rt, parser));
	}
//	else if (ft_str_next_is(str, "camera"))
//	{
//		parser->cur += ft_strlen("camera");
//		return (cmd_set_camera(rt, parser));
//	}
	else
		return (msg_warn("Syntax error: Unknown object type"));
	return (msg_oks("oks"));
}
