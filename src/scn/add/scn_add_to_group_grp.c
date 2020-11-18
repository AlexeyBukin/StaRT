//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"

int 			scn_add_to_group_grp(t_scn *scn, t_obj *dest, t_obj *grp)//TODO make like in scn_add_to_group_obj
{
	if (scn == NULL || dest == NULL || grp == NULL)
		return (rt_err("scn_add_to_group_grp(): Given pointer is NULL"));
	if (grp->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_grp(): given obj is not a container"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_grp(): dest is not a group"));
	if ((scn_name_check(scn, grp->name)))
		return (rt_err("scn_add_to_group_grp(): id collision"));
	return (realloc_group_add_obj(&dest->content.group, grp));
}
