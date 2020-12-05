
#include "rt.h"

int				scn_remove_by_name_cam(t_scn *scn, char *name)
{
	t_obj		*obj;

	if (!scn || !name)
		return (rt_err("scn_remove_by_name_cam(): was given a NULL pointer"));
	if (!(obj = scn_get_obj_by_name(scn, name)))
		return (rt_err("scn_remove_by_name_cam(): obj with given name does not exist"));
	if (obj->type != OBJ_CAMERA)
		return (rt_err("scn_remove_by_name_cam(): obj with given name is not an object"));
	if (scn_del_copies_of(scn->main_group, obj))
		return (rt_err("scn_remove_by_name_cam():"
					   " del_obj_copies(): couldn't delete copies"));
	if (grp_remove_by_name(obj->parent, obj->name))
		return (rt_err("scn_remove_by_name_cam(): couldn't delete copy"));
	return (obj_deinit(obj));
}
