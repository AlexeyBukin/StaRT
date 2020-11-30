//
// Created by Hugor Chau on 11/30/20.
//

#include "rt.h"

int				scn_remove_by_name_lgt(t_scn *scn, char *name)
{
	t_obj		*obj;

	if (!scn || !name)
		return (rt_err("scn_remove_by_name_obj(): was given a NULL pointer"));
	if (!(obj = scn_get_obj_by_name(scn, name)))
		return (rt_err("scn_remove_by_name_obj(): obj with given name does not exist"));
	if (obj->type != OBJ_LIGHT)
		return (rt_err("scn_remove_by_name_obj(): obj with given name is not an object"));
	if (scn_del_copies_of(scn->main_group, obj))
		return (rt_err("scn_remove_by_name_obj():"
					   " del_obj_copies(): couldn't delete copies"));
	if (grp_remove_by_name(obj->parent, obj->name))
		return (rt_err("scn_remove_by_name_copy(): couldn't delete copy"));
	return (obj_deinit(obj));
}
