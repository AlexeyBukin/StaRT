//
// Created by Hugor Chau on 11/9/20.
//

#include "rt.h"

/*
**		internal scene function:
**		using this at the moment of creating
**		an object in scn_get_obj/scn_get_shape
*/

int 			map_add_elem(t_map *map, t_elem *obj)
{
	t_element		*tmp;
	uint			index;
	t_element		*curr;

	index = obj->id % MAP_ARRAY_LEN;
	tmp = map->elements[index];
	if (((map->elements[index]) = (t_element *)ft_memalloc(sizeof(t_element))) == NULL)
	{
		map->elements[index] = tmp;
		return (rt_err("map_add_obj(): malloc crashed"));
	}
	curr = map->elements[index];
	(curr)->id = obj->id;
	(curr)->name = ft_strdup(obj->name);
	(curr)->next = tmp;
	return (0);
}

static t_element	*element_by_id(struct s_scn *scn, uint id)
{
	t_element		*curr;

	curr = scn->id_to_name.elements[id % MAP_ARRAY_LEN];
	while (curr)
	{
		if (curr->id == id)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		rt_warn("scn_name_by_id(): couldn't find id");
		return (NULL);
	}
	return (curr);
}

/*
**		TODO: entry point:
**		use it if you wanna find
**		name by id
*/

char				*scn_name_by_id(struct s_scn *scn, uint id)
{
	t_element		*element;

	if ((element = element_by_id(scn, id)) == NULL)
		return (NULL);
	return (element->name);
}
