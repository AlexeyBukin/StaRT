//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"


//int				delete_copy(t_obj *obj)
//{
//	t_obj			**children;
//	t_obj_group 	*parent;
//
//	if (!(obj->parent))
//		return (rt_err("scn_remove_by_name_copy():"
//		" obj has no parent"));
//	parent = &obj->parent->content.group;
////	if (obj->parent->group->type != OBJ_GROUP)
////
////	children = (t_obj **)ft_memalloc(sizeof(t_obj *)
////			* (parent->child_num - 1));
////	if (!children)
////		return (rt_err("scn_remove_by_name_copy():"
////		" malloc returned NULL pointer"));
////	grp_memmove(parent, children, obj);
////	ft_free(parent->children);
//	parent->children = children;
//	parent->child_num--;
//	return (0);
//}

int				scn_remove_by_name_copy(t_scn *scn, char *name)
{
	t_obj		*obj;

	if (!scn || !name)
		return (rt_err("scn_remove_by_name_copy(): was given a NULL pointer"));
	if (!(obj = scn_get_obj_by_name(scn, name)))
		return (rt_err("scn_remove_by_name_copy(): obj with given name does not exist"));
//	if (obj->type != OBJ_COPY)
//		return (rt_err("scn_remove_by_name_copy(): obj with given name is not a copy"));
	if (grp_remove_by_name(obj->parent, name))
		return (rt_err("scn_remove_by_name_copy(): couldn't delete copy"));
	return (obj_deinit(obj));
}
