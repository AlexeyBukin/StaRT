//
// Created by Hugor Chau on 11/10/20.
//

#include "rt.h"

/*
**		TODO your entry point functions too, Sanya
*/

t_sphere				*scn_get_sphere(t_scn *scn, char *name)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = scn_get_obj(scn, name);
	if (obj == NULL)
		return (NULL);
	obj->type = OBJ_SPHERE;
	sphere = &obj->shape.sphere;
	return (sphere);
}

struct s_plane			*scn_get_plane(t_scn *scn, char *name)
{
	t_obj			*obj;
	struct s_plane	*plane;

	obj = scn_get_obj(scn, name);
	if (obj == NULL)
		return (NULL);
	obj->type = OBJ_PLANE;
	plane = &obj->shape.plane;
	return (plane);
}

struct s_cone			*scn_get_cone(t_scn *scn, char *name)
{
	t_obj			*obj;
	struct s_cone	*cone;

	obj = scn_get_obj(scn, name);
	if (obj == NULL)
		return (NULL);
	obj->type = OBJ_CONE;
	cone = &obj->shape.cone;
	return (cone);
}


struct s_cylinder		*scn_get_cylinder(t_scn *scn, char *name)
{
	t_obj				*obj;
	struct s_cylinder	*cylinder;

	obj = scn_get_obj(scn, name);
	if (obj == NULL)
		return (NULL);
	obj->type = OBJ_CYLINDER;
	cylinder = &obj->shape.cylinder;
	return (cylinder);
}
