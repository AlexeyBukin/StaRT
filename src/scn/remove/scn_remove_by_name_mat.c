//
// Created by Hugor Chau on 11/17/20.
//
#include "rt.h"

void		mat_memmove(t_scn *scn, t_mat **materials, t_mat *mat)
{
	size_t		i;

	i = 0;
	while (i < scn->materials_num)
	{
		if (scn->materials[i] == mat)
		{
			i++;
			continue ;
		}
		*materials = scn->materials[i];
		materials++;
		i++;
	}
}

int		mat_del(t_scn *scn, t_mat *mat)
{
	t_mat		**materials;

	if (!(materials = (t_mat **)ft_memalloc(sizeof(t_mat *) * (scn->materials_num - 1))))
		return (rt_err("mat_remove_by_name(): malloc crashed"));
	mat_memmove(scn, materials, mat);
//	mat_deinit(mat);///TODO do we need to deinit this?
	free(scn->materials);
	scn->materials = materials;
	scn->materials_num--;
	return (0);
}

int		scn_remove_by_name_mat(t_scn *scn, char *name)
{
	t_mat		*mat_to_del;

	if (!scn || !name)
		return (rt_err("mat_remove_by_name(): was given a NULL pointer"));
	mat_to_del = scn_get_mat_by_name(scn, name);
	if (!mat_to_del)
		return (rt_err("mat_remove_by_name(): there is no"
					   " camera with given name"));
	return (mat_del(scn, mat_to_del));
}
