//
// Created by Hugor Chau on 11/9/20.
//

#ifndef RT_SCN_MAP_H
#define RT_SCN_MAP_H

#include "libft.h"

struct s_scn;

#define MAP_ARRAY_LEN 1024

typedef struct		s_element
{
	uint				id;
	char				*name;
//	void				*obj;
	struct s_element	*next;
}					t_element;

typedef struct		s_elem
{
	uint				id;
	char				*name;
}					t_elem;

//by id
typedef struct		s_map
{
	t_element		*elements[MAP_ARRAY_LEN];
}					t_map;

//needs for hash-function, avoiding collisions

//by name
typedef struct		s_hash_map
{
	t_element		*elements[MAP_ARRAY_LEN];
}					t_hash_map;

/*
**				scn_map
*/

int 			map_add_elem(t_map *map, t_elem *obj);//internal scene function
int 			map_remove_elem(struct s_scn *scn, uint id);

/*
**				scn_map_del (where should we call them?)
*/

char			*scn_name_by_id(struct s_scn *scn, uint id);
void 			scn_map_deinit(struct s_scn *scn);

/*
**				scn_hash_map
*/

t_obj			*hash_map_add(t_hash_map *map, t_elem *obj);
t_obj			*hash_map_remove(t_hash_map *map, t_elem *obj);
t_obj			*scn_id_by_name(struct s_scn *scn, char *name);

#endif
