
#include "rt.h"

int				cmd_set_plane_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->container == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cone_default(): was given a NULL pointer"));
	parser->object->content.container.shape_type = SHP_PLANE;
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->container->shape.plane.radius = 0.0;
	parser->object->visible = TRUE;
	parser->object->type = OBJ_CONTAINER;
	parser->material = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME);
	parser->texture = scn_get_txr_by_name(rt->scene, DEFAULT_TEXTURE_NAME);
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg				cmd_set_plane_read(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_plane(): bad syntax1"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("plane_parse_flags(): bad syntax in transform"));
		if (cmd_set_visibility(parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_grp(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax group"));
		if (cmd_set_mat(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax material"));
		if (cmd_set_name(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg				cmd_set_plane(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL)
		return(msg_err("cmd_add_plane(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_cone(): critical malloc error"));
	return (cmd_set_plane_read(rt, parser, dest));
}
