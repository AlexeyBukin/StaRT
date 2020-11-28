//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static t_msg			cmd_set_object(t_rt *rt, t_parser *parser, t_obj *obj)
{
	if (obj->type == OBJ_GROUP)
		return (cmd_set_group(rt, parser, obj));
	if (obj->type != OBJ_CONTAINER)
		return (msg_warn("cmd_set_object(): unknown object type"));
	if (obj->content.container.shape_type == SHP_CONE)
		return (cmd_set_cone(rt, parser, obj));
	if (obj->content.container.shape_type == SHP_SPHERE)
		return (cmd_set_sphere(rt, parser, obj));
	if (obj->content.container.shape_type == SHP_PLANE)
		return (cmd_set_plane(rt, parser, obj));
	if (obj->content.container.shape_type == SHP_CYLINDER)
		return (cmd_set_cylinder(rt, parser, obj));
	return (msg_warn("couldn\'t find object"));
}

t_msg			cmd_set_type(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp_obj;

	if (parser == NULL || rt == NULL)
		return(msg_err("cmd_set_obj(): given NULL pointer in cmd_add()"));
	if ((scn_get_mat_by_name(rt->scene, parser->name)))
		return (cmd_set_material(rt, parser));
	if ((scn_get_cam_by_name(rt->scene, parser->name)))
		return (cmd_set_camera(rt, parser));
	if ((tmp_obj = scn_get_obj_by_name(rt->scene, parser->name)))
		return (cmd_set_object(rt, parser, tmp_obj));
	return (msg_warn("cmd_set_obj(): can\'t recognise object type or shape"));
}

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
		return (msg_warn("cmd_set(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_set(): bad name"));
	if (check_default_names(parser))
	{
		ft_free(parser->name);
		return (msg_warn("cmd_set(): can\'t modify default object"));
	}
	return (cmd_set_type(rt, parser));
}
