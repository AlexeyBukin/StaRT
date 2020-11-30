//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

int		scn_move_obj(t_scn *scn, t_obj *dst, t_obj *obj)
{
	if (scn == NULL || obj == NULL)
		return (rt_err("scn_move_obj(): given NULL pointer"));
	if (dst == NULL)
		return (0);
	if (dst->type != OBJ_GROUP)
		return (rt_err("scn_move_obj(): destination is not group"));
	if (dst == obj)
		return (rt_err("can\'t move object to itself"));
	if (dst == obj->parent)
		return (rt_err("can\'t move object to it\'s parent"));
	if (dst != (scn_get_obj_by_name(scn, dst->name)))
		return (rt_err("scn_move_obj(): couldn\'t find given group in scene"));
	if (obj != (scn_get_obj_by_name(scn, obj->name)))
		return (rt_err("scn_move_obj(): couldn\'t find given obj in scene"));
	if (grp_remove_by_name(obj->parent, obj->name))
		return (rt_err("scn_move_obj(): couldn\'t remove obj from group"));
	if (scn_add_to_group(scn, dst, obj))
		return (rt_err("scn_move_obj(): couldn\'t add obj to group"));//remove copies or what?
	return (0);
}
