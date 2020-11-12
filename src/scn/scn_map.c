//
// Created by Hugor Chau on 11/9/20.
//

#include "rt.h"

static t_element	*element_by_id(struct s_scn *scn, uint id)
{
	t_element		*curr;

	curr = scn->id_to_name.elements[id % scn->id_to_name.curr_size];
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
