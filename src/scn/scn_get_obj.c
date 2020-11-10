//
// Created by Hugor Chau on 11/10/20.
//

#include "rt.h"


static int 	realloc_array(void **array, size_t elem_size, size_t max, size_t num)
{
	if (max > num)
		return (0);
	*array = ft_realloc(*array, elem_size * max,
						elem_size * (max + ALLOC_SIZE_STEP));
	if (*array == NULL)
		return (-1);
	return (0);
}

static int 	prepare_scn(t_scn *scn)
{
	if (scn == NULL)
		return (rt_err("prepare_scn(): scn is NULL pointer"));
	if (realloc_array((void **)&scn->objects,
						sizeof(t_obj),
						scn->objects_max,
						scn->objects_num) == -1)
		return (rt_err("prepare_scn(): malloc crashed"));
	if (realloc_array((void **)&scn->materials,
						sizeof(t_mat),
						scn->materials_max,
						scn->materials_num) == -1)
		return (rt_err("prepare_scn(): malloc crashed"));
	scn->objects_max += SIZE_STEP;
	return (0);
}

/*
**		TODO your entry point function, Sanya
*/

// or more universal:

void	*scn_get_element(t_scn *scn, char *name)
{
	if (prepare_scn(scn) != 0)
		return (NULL);
	if (ft_strcmp(name, GET_OBJ) == 0)
	{
		scn->objects_num++;
		//do we need to call scn_id() here or inside Sanya's functions?
		//cause if we'll do it here, we could dublicate it
		return (&scn->objects[scn->objects_num - 1]);
	}
	if (ft_strcmp(name, GET_MATERIAL) == 0)
	{
		scn->materials_num++;
		return (&scn->materials[scn->materials_num - 1]);
	}
	return (NULL);
}

t_obj	*scn_get_obj(t_scn *scn)//mb + obj_name? this means no extra functions
//after object creation and making equivalent in hash_map at the moment of
//creation
{
	ft_printf("%d\n", scn->objects_num);
	return (scn_get_element(scn, GET_OBJ));
}
