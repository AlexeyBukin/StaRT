//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

/*
**		it's for future me
*/

t_obj	*scn_obj_by_id(t_scn *scn, uint id)
{
	uint			max_obj;
	uint			curr_obj;
	struct s_obj	*objs;

	curr_obj = 0;
	objs = scn->objects;
	max_obj = scn->objects_num;
	while (max_obj < scn->objects_num)
	{
		if ((*objs).id == id)
			return (objs);
		objs++;
		max_obj++;
	}
	rt_err("scn_obj_by_id(): couldn't find object.");
	return (NULL);
}

int		set_obj_mid(t_scn *scn, uint obj_id, uint mid)
{
	t_obj		*obj;

	if (!(obj = scn_obj_by_id(scn, obj_id)))
		return (-1);
	if ((scn_check_mid(scn, obj_id)) == -1)
		return (-1);
	obj->material_id = mid;
	return (0);
}

/*
**		if you wanna check material id
*/

int		scn_check_mid(t_scn *scn, uint mid)
{
	struct s_mat	*materials;
	uint			materials_num;

	materials = scn->materials;
	materials_num = scn->materials_num;
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
