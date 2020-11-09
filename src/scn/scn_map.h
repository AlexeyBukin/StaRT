//
// Created by Hugor Chau on 11/9/20.
//

#ifndef DDD_SCN_MAP_H
#define DDD_SCN_MAP_H

#include "libft.h"

int				map_add_obj();
int				map_remove_obj();
int				map_get_obj();

int				hash_map_add();
int				hash_map_remove();
int				hash_map_get();

typedef struct		s_elements
{
	uint			id;
	char			*name;
	t_list			content;
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

#endif //DDD_SCN_MAP_H
