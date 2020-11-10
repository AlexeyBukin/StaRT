//
// Created by Hugor Chau on 11/9/20.
//

#include "rt.h"

static t_obj	*get_plane(t_scn *scn, uint plane_id)
{
	t_obj		*obj;

	if (!(obj = scn_obj_by_id(scn, plane_id)))
		return (NULL);
	if (obj->type != OBJ_PLANE)
	{
		rt_err("scn_set_sphere_radius(): obj_id error: "
			   "it's not a sphere");
		return (NULL);
	}
	return (obj);
}

int		scn_set_plane_distance(t_scn *scn, uint plane_id, float d)
{
	t_obj		*obj;

	if (!(obj = get_plane(scn, plane_id)))
		return (-1);
	obj->shape.plane.d = d;
	return (0);
}

int		scn_set_plane_norm(t_scn *scn, uint plane_id, t_vec3 n)
{
	t_obj		*obj;

	if (!(obj = get_plane(scn, plane_id)))
		return (-1);
	obj->shape.plane.n = n;
	return (0);
}

int		scn_set_plane_mid(t_scn *scn, uint obj_id, uint mid)
{
	return (set_obj_mid(scn, obj_id, mid));
}
