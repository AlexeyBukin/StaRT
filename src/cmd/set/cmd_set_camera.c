
#include "rt.h"

t_msg               cmd_set_cametra_flags(t_cam *dest, t_parser *parser)
{
    if (dest == NULL || parser == NULL)
        return (msg_err ("NULL in cmd_set_cametra_flags"));
    while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("camera_parse_flags(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (msg_warn("camera_parse_flags(): bad syntax in fov"));
	}
    ft_memcpy(dest, parser->camera, sizeof(t_cam));
    return (msg_oks("camera set done"));
}

t_msg				cmd_set_camera(t_rt *rt, t_parser *parser)
{
	t_cam			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_camera"));
	parser->cur += ft_strlen("camera");
	if (cmd_read_space_req(&parser->cur))
		return(msg_warn("bad syntax: no space after camera"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_set_camera: bad name"));
	if ((tmp = scn_get_cam_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("no camera with this name found"));
	parser->camera = ft_memalloc(sizeof(t_cam));
	ft_memcpy(parser->camera, tmp, sizeof(t_cam));
	return (cmd_set_camera_flags(tmp, parser));
}
