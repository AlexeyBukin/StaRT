#include "rt.h"

static int			cmd_read_fov(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		return (cmd_read_vec2(&(parser->cur), &(parser->camera->fov)));
	}
	return (0);
}

t_msg	    cmd_parse_camera_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser))
			return (msg_warn("camera_parse_flags(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (msg_warn("camera_parse_flags(): bad syntax in fov"));
	}
	scn_add_cam(rt->scene, parser->camera);
	return (msg_oks("it works!"));
}
