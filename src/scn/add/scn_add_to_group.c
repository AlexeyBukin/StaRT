//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

int 			scn_add_to_group(t_scn *scn, t_obj *dest, t_obj *obj)
{
	if (scn == NULL || dest == NULL || obj == NULL)
		return (rt_err("scn_add_to_group(): Given pointer is NULL"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group(): dest is not a group"));
	if (obj->type == OBJ_COPY)
		return (scn_add_to_group_copy(scn, dest, obj));
	if (obj->type == OBJ_GROUP)
		return (scn_add_to_group_grp(scn, dest, obj));
	if (obj->type == OBJ_CONTAINER)
		return (scn_add_to_group_obj(scn, dest, obj));
	return (0);
}
