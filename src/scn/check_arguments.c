//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"
#define SIZE_STEP	16
#define ERROR		-1

static int		check_mid(struct s_mat *materials, uint materials_num, uint mid)
{
	if (mid == 0)
	{
		rt_warn("check_id(): material id == 0");
		return (0);
	}
	while (materials_num > 0)
	{
		materials_num--;
		if ((*materials).id == mid)
			return (0);
		materials++;
	}
	rt_err("check_mid(): wrong material id!");
	return (-1);
}

static int 	prepare_scn(t_scn *scn)
{
	if (scn == NULL)
	{
		rt_err("prepare_scn(): scn is NULL pointer");
		return (-1);
	}
	if (scn->objects_max >= scn->objects_num)
		return (0);
	scn->objects = ft_realloc(scn->objects, sizeof(t_obj) * scn->objects_max,
							  sizeof(t_obj) * (scn->objects_max + SIZE_STEP));
	scn->objects_max += SIZE_STEP;
	if (scn->objects == NULL)
	{
		rt_err("prepare_scn(): malloc crashed");
		return (-1);
	}
	return (0);
}

int		check_arguments(t_scn *scn, uint mid)
{
	if (prepare_scn(scn))
		return (-1);
	if (check_mid(scn->materials, scn->materials_num, mid) == -1)
		return (-1);
	return (0);
}
