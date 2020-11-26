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
		return (cmd_set_cone(rt, parser));
	if (ft_str_next_is(str, "plane"))
		return (cmd_set_plane(rt, parser));
	if (ft_str_next_is(str, "cylinder"))
		return (cmd_set_cylinder(rt, parser));
	if (ft_str_next_is(str, "sphere"))
		return (cmd_set_sphere(rt, parser));
	if (ft_str_next_is(str, "group"))
		return (cmd_set_group(rt, parser));
	if (ft_str_next_is(str, "material"))
		return (cmd_set_material(rt, parser));
	if (ft_str_next_is(str, "camera"))
		return (cmd_set_camera(rt, parser));
//	else if (ft_str_next_is(str, "camera"))
//	{
//		parser->cur += ft_strlen("camera");
//		return (cmd_set_camera(rt, parser));
//	}
	return (msg_warn("Syntax error: Unknown object type"));
}
