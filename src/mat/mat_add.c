//
// Created by Hugor Chau on 11/17/20.
//

#include "rt.h"

int		mat_add(t_scn *scn, t_mat *mat)
{
	t_mat		**new_array;
	t_mat		*copy;

	if ((copy = scn_get_mat_by_name(scn, mat->name)))
	{
		if (copy == mat)
			return (rt_err("mat_add(): object is inside the scene already"));
		mat_deinit(mat);
		return (rt_err("mat_add(): name collision"));
	}
	if (!(new_array = (t_mat **)ft_realloc(scn->materials, sizeof(t_mat *) * scn->materials_num,
										   sizeof(t_mat *) * (scn->materials_num + 1))))
	{
		mat_deinit(mat);
		return (rt_err("mat_add(): malloc returned NULL pointer"));
	}
	scn->materials = new_array;
	scn->materials_num++;
	scn->materials[scn->materials_num - 1] = mat;
	return (0);
}
