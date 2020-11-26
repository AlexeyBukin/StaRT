
#include "rt.h"

int 				cmd_set_camera_default(t_rt *rt, t_parser *parser)
{
	(void)rt;
	if (parser == NULL || parser->transform == NULL)
		return (rt_err("cmd_set_camera_default(): was given a NULL pointer"));
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->camera->fov = vec2_zero();
	return (0);
}

static t_msg			init_camera_parser(t_rt *rt, t_parser *parser)
{
	if (cam_init(&parser->camera, parser->name))
		return (msg_err("Criticall err malloc"));
	parser->transform = &parser->camera->transform;
	if (cmd_set_camera_default(rt, parser))
		return (msg_warn("Given a NULL pointer"));
	return (msg_oks("ok"));
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
	parser->object->name = parser->name;
	init_camera_parser(rt, parser);
	return (cmd_parse_camera_flags(rt, parser));
}
