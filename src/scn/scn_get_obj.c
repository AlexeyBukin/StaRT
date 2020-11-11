//
// Created by Hugor Chau on 11/10/20.
//

#include "rt.h"

static int 	realloc_array(void **array, size_t elem_size, uint *max, uint num)
{
	if (*max > num)
		return (0);
	*array = ft_realloc(*array, elem_size * *max,
						elem_size * (*max + ALLOC_SIZE_STEP + 1));
	if (*array == NULL)
		return (-1);
	*max += ALLOC_SIZE_STEP;
	return (0);
}

static int 	prepare_scn(t_scn *scn)
{
	if (scn == NULL)
		return (rt_err("prepare_scn(): scn is NULL pointer"));
	if (realloc_array((void **)&scn->objects,
						sizeof(t_obj),
						&scn->objects_max,
						scn->objects_num) == -1)
		return (rt_err("prepare_scn(): malloc crashed"));
	if (realloc_array((void **)&scn->materials,
						sizeof(t_mat),
						&scn->materials_max,
						scn->materials_num) == -1)
		return (rt_err("prepare_scn(): malloc crashed"));
	return (0);
}

void	*create_element(t_scn *scn, t_elem *obj, char *name)
{
	if (obj == NULL)
		return (NULL);
	obj->id = scn_id();
	obj->name = ft_strdup(name);
	(map_add_elem(&scn->id_to_name, obj));
//	(hashmap_add_elem(obj));
	return (obj);
}

void	*scn_get_element(t_scn *scn, char *name)
{
	if (prepare_scn(scn) != 0)
		return (NULL);
	if (ft_strcmp(name, GET_OBJ) == 0)
	{
		scn->objects_num++;
		return (&scn->objects[scn->objects_num - 1]);
	}
	if (ft_strcmp(name, GET_MATERIAL) == 0)
	{
		scn->materials_num++;
		return (&scn->materials[scn->materials_num - 1]);
	}
	return (NULL);
}

/*
**		TODO your entry point function, Sanya
*/

t_obj	*scn_get_obj(t_scn *scn, char *obj_name)
{
	t_obj		*obj;

	obj = scn_get_element(scn, GET_OBJ);
	create_element(scn, (t_elem *)obj, obj_name);
	return (obj);
}
