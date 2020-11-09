//
// Created by Hugor Chau on 11/9/20.
//

#include "rt.h"

static t_obj	*get_sphere(t_scn *scn, uint sphere_id)
{
	t_obj		*obj;

	if (!(obj = scn_obj_by_id(scn, sphere_id)))
		return (NULL);
	if (obj->type != OBJ_SPHERE)
	{
		rt_err("scn_set_sphere_radius(): obj_id error: "
			   "it's not a sphere");
		return (NULL);
	}
	return (obj);
}

int		scn_set_sphere_radius(t_scn *scn, uint sphere_id, float r)
{
	t_obj		*obj;

	if (r < 0)
	{
		rt_err("scn_add_sphere(): make_sphere(): radius is less than zero!");
		return (-1);
	}
	if (!(obj = get_sphere(scn, sphere_id)))
		return (-1);
	obj->shape.sphere.r = r;
	return (0);
}

int		scn_set_sphere_pos(t_scn *scn, uint sphere_id, t_vec3 pos)
{
	t_obj		*obj;

	if (!(obj = get_sphere(scn, sphere_id)))
		return (-1);
	obj->shape.sphere.pos = pos;
	return (0);
}

int		scn_set_sphere_mid(t_scn *scn, uint obj_id, uint mid)
{
	return (set_obj_mid(scn, obj_id, mid));
}
