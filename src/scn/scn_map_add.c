
#include "rt.h"

void			add_elem(t_map *map, t_element **element, uint *i)
{
	uint			index;
	t_element		*iter;
	uint			j;

	index = (*element)->id % map->curr_size;
	if (!map->elements[index])
		map->elements[index] = *element;
	else
	{
		iter = map->elements[index];
		j = 0;
		while (iter->next)
		{
			iter = iter->next;
			j++;
		}
		iter->next = *element;
		*i = j;
	}
}

void			resort_list(t_map *map, t_element *old_elems)
{
	uint			extra;
	t_element		*iter;
	t_element		*tmp;

	iter = old_elems;
	while (iter)
	{
		tmp = iter->next;
		iter->next = NULL;
		add_elem(map, &iter, &extra);
		iter = tmp;
	}
}

int			realloc_map(t_map *map)
{
	uint			i;
	t_element		**old_elems;
	uint			old_size;

	old_elems = map->elements;
	old_size = map->curr_size;
	map->curr_size += MAP_STEP_SIZE;
	if (!(map->elements = (t_element **)ft_memalloc(sizeof(t_element *) * (map->curr_size))))
		return (rt_err("map_add_elem(): realloc_map(): malloc crashed"));
	i = 0;
	while (i < old_size)
	{
		resort_list(map, (old_elems)[i]);
		i++;
	}
	ft_memdel((void *)&(old_elems));
	return (0);
}

void			fill_elem(t_element *element, t_elem *obj)
{
	element->id = obj->id;
	element->name = ft_strdup(obj->name);
	element->next = NULL;
}

/*
**		internal scene function:
**		using this at the moment of creating
**		an object in scn_get_obj/scn_get_shape;
**		everything else in this file is aim to
**		realise this function
*/

int 			map_add_elem(t_map *map, t_elem *obj)
{
	static uint		i = 0;
	t_element		*tmp;

	if ((tmp = (t_element *)ft_memalloc(sizeof(t_element))) == NULL)
		return (rt_err("map_add_obj(): malloc crashed"));
	fill_elem(tmp, obj);
	if (i == 5)
	{
		realloc_map(map);
		i = 0;
	}
	add_elem(map, &tmp, &i);
	return (0);
}
