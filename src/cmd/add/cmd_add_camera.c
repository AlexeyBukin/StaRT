
#include "rt.h"

int			cmd_read_fov(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		return (cmd_read_vec2(&(parser->cur), &(parser->object->content.camera.fov)));
	}
	return (0);
}

static t_msg	    cmd_parse_camera_flags(t_rt *rt, t_parser *parser)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser))
			return (cmd_add_error(parser, "camera_parse_flags(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (cmd_add_error(parser, "camera_parse_flags(): bad syntax in fov"));
		if (cmd_set_obj_visibility(parser))
			return (cmd_set_error(parser, "cmd_set_camera(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser))
			return (cmd_set_error(parser, "cmd_set_camera(): bad syntax group"));
	}
	return (cmd_add_obj_to_scn(rt, parser));
}

static int			init_camera_parser(t_rt *rt, t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CAMERA))
		return (rt_err("Criticall err malloc"));
	parser->object->transform.rot_local = mat3x3_identity();
	parser->transform = &parser->object->transform;
	parser->group = rt->scene->main_group;
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
	if (init_camera_parser(rt, parser))
		return (msg_err("cmd_add_camera(): critical malloc error"));
	return (cmd_parse_camera_flags(rt, parser));
}
