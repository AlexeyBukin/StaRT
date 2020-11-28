
#include "rt.h"

static t_msg		set_camera_error(t_parser *parser, char *message)
{
	cam_deinit(parser->camera);
	ft_free(parser->name);
	return (msg_warn(message));
}

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

static t_msg               cmd_set_camera_flags(t_rt *rt, t_cam *dest, t_parser *parser)
{
    if (dest == NULL || parser == NULL)
        return (msg_err ("NULL in cmd_set_cametra_flags"));
    while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (set_camera_error(parser, "cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser))
			return (set_camera_error(parser, "cmd_set_camera(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (set_camera_error(parser, "cmd_set_camera(): bad syntax in fov"));
		if (cmd_set_obj_name(rt, parser))
			return (set_camera_error(parser, "cmd_set_camera(): bad syntax visibility"));
	}
    ft_memcpy(dest, parser->camera, sizeof(t_cam));
    dest->name = ft_strdup(parser->name);
	cam_deinit(parser->camera);
	ft_free(parser->name);
    return (msg_oks("camera set done"));
}

static int			init_camera_parser(t_parser *parser, t_cam *src)
{
	if ((parser->camera = (t_cam *)ft_memalloc(sizeof(t_cam))) == NULL)
		return (rt_err("Criticall err malloc"));
	ft_memcpy(parser->camera, src, sizeof(t_cam));
	parser->camera->name = ft_strdup(parser->name);
	parser->transform = &parser->camera->transform;
	return (0);
}

t_msg				cmd_set_camera(t_rt *rt, t_parser *parser)
{
	t_cam			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_camera"));
	if ((tmp = scn_get_cam_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("no camera with this name found"));
	if (init_camera_parser(parser, tmp))
		return (msg_err("cmd_set_camera(): critical malloc error"));
	return (cmd_set_camera_flags(rt, tmp, parser));
}
