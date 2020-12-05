//
// Created by Hugor Chau on 11/30/20.
//

#include "rt.h"

static t_msg			cmd_set_object_type(t_rt *rt, t_parser *parser, t_obj *obj)
{
	if (obj->type == OBJ_GROUP)
		return (cmd_set_group(rt, parser, obj));
	if (obj->type == OBJ_LIGHT)
		return (cmd_set_light(rt, parser, obj));
	if (obj->type == OBJ_COPY)
		return (cmd_set_copy(rt, parser, obj));
	if (obj->type == OBJ_CAMERA)
		return (cmd_set_camera(rt, parser, obj));
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

t_msg			cmd_set_object(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp_obj;

	if (parser == NULL || rt == NULL)
		return(msg_err("cmd_set_obj(): given NULL pointer in cmd_add()"));
	if ((scn_get_mat_by_name(rt->scene, parser->name)))
		return (cmd_set_material(rt, parser));
	if ((scn_get_txr_by_name(rt->scene, parser->name)))
		return (cmd_set_txr(rt, parser));
	if ((tmp_obj = scn_get_obj_by_name(rt->scene, parser->name)))
		return (cmd_set_object_type(rt, parser, tmp_obj));
	ft_free(parser->name);
	return (msg_warn("cmd_set_obj(): can\'t recognise object type or shape"));
}
