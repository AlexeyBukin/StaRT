//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

int		make_cone(t_obj *obj, t_vec3 pos, t_vec3 cap, float r)
{
	t_cone	cone;

	if (r <= 0)
	{
		rt_err("scn_add_cone(): make_cone(): radius is less than zero!");
		return (-1);
	}
	cone.r = r;
	cone.pos = pos;
	cone.cap = cap;
	obj->id = scn_id();
	obj->type = OBJ_CONE;
	obj->shape.cone = cone;
	return (0);
}

int		scn_add_cone(t_scn *scn, t_vec3 pos, float r, t_vec3 cap, uint mid)//TODO 5 arguments, discuss with Sanya
{
	check_arguments(scn, mid);
	if (make_cone(&scn->objects[scn->objects_num], pos, cap, r) == -1)
		return (-1);
	scn->objects[scn->objects_num].material_id = mid;
	scn->objects_num++;
	return (0);
}
