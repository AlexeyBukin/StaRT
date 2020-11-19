
#include "rt.h"

int 			scn_add_to_group_copy(t_scn *scn, t_obj *dest, t_obj *copy)//TODO make like in scn_add_to_group_obj
{
	if (scn == NULL || dest == NULL || copy == NULL)
		return (rt_err("scn_add_to_group_copy(): Given pointer is NULL"));
	if (copy->type != OBJ_COPY)
		return (rt_err("scn_add_to_group_copy(): given obj is not a copy"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_copy(): dest is not a group"));
	if ((scn_name_check(scn, copy->name)))
		return (rt_err("scn_add_to_group_copy(): id collision"));
	if (scn_group_inc(&dest->content.group))
		return (rt_err(""));
	dest->content.group.children[dest->content.group.child_num - 1] = copy;
	copy->parent = dest;
	copy->transform.parent = &(dest->transform);
	return (0);
}
