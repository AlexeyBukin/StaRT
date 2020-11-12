//
// Created by Hugor Chau on 11/11/20.
//

#include "rt.h"

#include "rt.h"

static void			remove_elem(t_element **to_del)
{
	if (to_del == NULL || *to_del == NULL)
		return;
	ft_strdel(&((*to_del)->name));
	(*to_del)->next = NULL;
	ft_memdel((void **)to_del);
}

int				map_find_and_del(t_map *map, uint id)
{
	t_element		*next;
	t_element		*element;

	element = map->elements[id % map->curr_size];
	while (element->next)
	{
		if (element->next->id == id)
			break ;
		element = element->next;
	}
	if (!element || !element->next)
		return (rt_err("map_remove_obj(): couldn't find id"));
	next = element->next->next;
	remove_elem(&(element->next));
	element->next = next;
	return (0);
}

/*
**		TODO: entry point:
**		I'm not sure where should we
**		destroy an object,
**		but this is function,
**		that could destroy it's mentioning in map
*/

int 			map_remove_elem(struct s_scn *scn, uint id)
{
	t_element		*element;
	t_map			*map;
	t_element		*tmp;
	uint			index;

	map = &scn->id_to_name;
	index = id % map->curr_size;
	element = map->elements[index];
	if (element == NULL)
		return (rt_err("map_remove_obj(): couldn't find id"));
	if (element->id == id)
	{
		tmp = element->next;
		remove_elem(&map->elements[index]);
		map->elements[index] = tmp;
		return (0);
	}
	return (map_find_and_del(map, id));
}

/*
**		TODO: entry point:
**		I'm not sure where should we
**		destroy map,
**		but hey, here I am,
**		deleting map
*/

void 			scn_map_deinit(t_scn *scn)
{
	uint			i;
	t_element		*element;
	t_element		*tmp;
	t_map			*map;

	i = 0;
	map = &scn->id_to_name;
	while (i < map->curr_size)
	{
		element = map->elements[i];
		while (element)
		{
			tmp = element->next;
			remove_elem(&element);
			element = tmp;
		}
		map->elements[i] = NULL;
		i++;
	}
}