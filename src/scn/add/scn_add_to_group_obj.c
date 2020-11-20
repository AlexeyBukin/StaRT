
#include "rt.h"

int 			scn_add_to_group_obj(t_scn *scn, t_obj *dest, t_obj *obj)
{
	if (scn == NULL || dest == NULL || obj == NULL)
		return (rt_err("scn_add_to_group_obj(): Given pointer is NULL"));
	if (obj->type != OBJ_CONTAINER)//the only one string that has the difference
		return (rt_err("scn_add_to_group_obj(): given obj is not a container"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_obj(): dest is not a group"));
	if ((scn_name_check(scn, obj->name)))
		return (rt_err("scn_add_to_group_obj(): name collision"));
	if (scn_group_inc(&dest->content.group))
		return (rt_err(""));
	dest->content.group.children[dest->content.group.child_num - 1] = obj;
	obj->parent = dest;
	obj->transform.parent = &(dest->transform);
	return (0);
}
