//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

int		make_sphere(t_obj *obj, t_vec3 pos, float r)
{
	t_sphere	sphere;

	if (obj == NULL)
	{
		rt_err("scn_add_sphere(): obj is NULL pointer");
	}
	if (r <= 0)
	{
		rt_err("scn_add_sphere(): make_sphere(): radius is less than zero!");
		return (-1);
	}
	sphere.r = r;
	sphere.pos = pos;
	obj->id = scn_id();
	obj->type = OBJ_SPHERE;
	obj->shape.sphere = sphere;
	return (0);
}

int		scn_add_sphere(t_scn *scn, t_vec3 pos, float r, uint mid)
{
	check_arguments(scn, mid);
	if (make_sphere(&scn->objects[scn->objects_num], pos, r) == -1)
		return (-1);
	scn->objects[scn->objects_num].material_id = mid;
	scn->objects_num++;
	return (0);
}
