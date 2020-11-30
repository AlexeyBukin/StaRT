
#include "rt.h"

int			cmd_read_fov(t_parser *parser)
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

static t_msg		add_camera_error(t_parser *parser, char *message)
{
	ft_free(parser->camera);
	ft_free(parser->name);
	return (msg_warn(message));
}

static t_msg	    cmd_parse_camera_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (add_camera_error(parser, "cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser))
			return (add_camera_error(parser, "camera_parse_flags(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (add_camera_error(parser, "camera_parse_flags(): bad syntax in fov"));
	}
	if (scn_add_cam(rt->scene, parser->camera))
		return (add_camera_error(parser, "couldn\'t add camera to scene"));
	return (msg_oks("camera added successfully"));
}

static int			init_camera_parser(t_parser *parser)
{
	if (cam_init(&parser->camera, parser->name))
		return (rt_err("Criticall err malloc"));
	parser->camera->transform.rot_local = mat3x3_identity();
	parser->transform = &parser->camera->transform;
	return (0);
}

t_msg           cmd_add_camera(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_camera(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("camera");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_camera(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_camera(): bad name"));
	if (init_camera_parser(parser))
		return (msg_err("init_camera_parser(): critical malloc error"));
	return (cmd_parse_camera_flags(rt, parser));
}
