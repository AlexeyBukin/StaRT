//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

int		make_plane(t_obj *obj, t_vec3 n, float d)
{
	struct s_plane		plane;

	plane.n = n;
	plane.d = d;
	obj->id = scn_id();
	obj->type = OBJ_PLANE;
	obj->shape.plane = plane;
	return (0);
}

int		scn_add_plane(t_scn *scn, t_vec3 n, float d, uint mid)
{
	check_arguments(scn, mid);
	if (make_plane(&scn->objects[scn->objects_num], n, d) == -1)
		return (-1);
	scn->objects[scn->objects_num].material_id = mid;
	scn->objects_num++;
	return (0);
}
