//
// Created by Hugor Chau on 11/9/20.
//

#ifndef RT_SCN_MAP_H
#define RT_SCN_MAP_H

#include "libft.h"

typedef struct		s_element
{
	uint				id;
	char				*name;
	// obj: mb it would be comfy to make pointers
	// to objects and get it when we alloc objects it scene?
	// it means that we need to generate id's when we alloc this shit
	void				*obj;//or just t_list?
	struct s_element	*next;//or just t_list?
}					t_elements;

//by id
typedef struct		s_map
{
	t_elements		elements[16];
}					t_map;

//needs for hash-function, avoiding collisions

//by name
typedef struct		s_hash_map
{
	t_elements		elements[16];
}					t_hash_map;

t_obj			*map_add_obj(t_map *map);
t_obj			*map_remove_obj(t_map *map);
t_obj			*map_get_obj(t_map *map);

t_obj			*hash_map_add(t_hash_map *map);
t_obj			*hash_map_remove(t_hash_map *map);
t_obj			*hash_map_get(t_hash_map *map);

#endif
