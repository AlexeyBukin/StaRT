//
// Created by Hugor Chau on 11/26/20.
//

#include "rt.h"

static t_msg			cmd_set_object(t_rt *rt, t_parser *parser, t_obj *obj)
{
	if (obj->type == OBJ_GROUP)
		return (cmd_set_group(rt, parser, obj));
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

t_msg			cmd_set_obj(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp_obj;
	t_cam		*tmp_cam;
	t_mat		*tmp_mat;

	if (parser == NULL || rt == NULL)
		return(msg_err("cmd_set_obj(): given NULL pointer in cmd_add()"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_set_obj(): bad name"));
	if ((tmp_mat = scn_get_mat_by_name(rt->scene, parser->name)))
		return (cmd_set_material(rt, parser));
	if ((tmp_cam = scn_get_cam_by_name(rt->scene, parser->name)))
		return (cmd_set_camera(rt, parser));
	if ((tmp_obj = scn_get_obj_by_name(rt->scene, parser->name)))
		return (cmd_set_object(rt, parser, tmp_obj));
	return (msg_warn("cmd_set_obj(): can\'t recognise object type or shape"));
}

t_msg			cmd_set_obj_to_scn(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL || dest == NULL)
		return (msg_warn("cmd_set_obj_to_scn(): given NULL pointer"));
	ft_memcpy(dest, parser->object, sizeof(t_obj));
	dest->name = parser->name;
	if (dest->type != OBJ_GROUP)
	{
		dest->content.container.material = parser->material;
	}
	if (parser->group != dest->parent && parser->group != NULL)
		scn_move_obj(rt->scene, parser->group, dest);
	return (msg_oks("oks"));
}
