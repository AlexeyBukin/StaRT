//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

int		make_cylinder(t_obj *obj, t_vec3 pos, t_vec3 cap, float r)
{
	struct s_cylinder	cylinder;

	if (r <= 0)
	{
		rt_err("scn_add_cylinder(): make_cylinder(): radius is less than zero!");
		return (-1);
	}
	cylinder.r = r;
	cylinder.pos = pos;
	cylinder.cap = cap;
	obj->id = scn_id();
	obj->type = OBJ_CYLINDER;
	obj->shape.cylinder = cylinder;
	return (0);
}

int		scn_add_cylinder(t_scn *scn, t_vec3 pos, t_vec3 cap, float r, uint mid)//TODO 5 arguments
{
	check_arguments(scn, mid);
	if (make_cylinder(&scn->objects[scn->objects_num], pos, cap, r) == -1)
		return (-1);
	scn->objects[scn->objects_num].material_id = mid;
	scn->objects_num++;
	return (0);
}
