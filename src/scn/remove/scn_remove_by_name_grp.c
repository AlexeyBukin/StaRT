//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"

//int				scn_remove_group_copies_rec(t_obj *from, t_obj *target)
//{
//	t_obj_group		*from_grp;
//	t_obj_group		*target_grp;
//	size_t		i;
//	int			error_flag;
//
//	i = 0;
//	error_flag = 0;
//	if (from == NULL || target == NULL)
//		return (rt_err("Given pointer is NULL"));
//	from_grp = &(from->content.group);
//	target_grp = &(target->content.group);
//	while (i < from_grp->child_num)
//	{
//		if (grp->children[i]->type == OBJ_GROUP)
//			if (scn_remove_group_copies_rec(grp->children[i], target))
//				return (rt_err(""));
//
//		if (from_grp->children[i]->type == OBJ_CONTAINER)
//			error_flag = del_obj_copies(main_group, grp->children[i]);
//		else if (grp->children[i]->type == OBJ_COPY)
//			error_flag = delete_copy(grp->children[i]);
//		else if (grp->children[i]->type == OBJ_GROUP)
//			error_flag = delete_group(main_group, &grp->children[i]->content.group);
//		if (error_flag == -1)
//			return (rt_err("delete_group(): couldn't delete object"));
//		i++;
//	}
//	return (error_flag);
//}
//

// deletes all copies of objects in given group and copies of group

int				scn_del_copies_rec(t_obj *main_group, t_obj *target)
{
	t_obj_group		*target_grp;
	size_t			i;
	int				error_flag;


	error_flag = 0;
	if (main_group == NULL || target == NULL)
		return (rt_err("Given pointer is NULL"));
	if (target->type == OBJ_COPY)
		return (0);
	if (target->type != OBJ_GROUP)
	{
		if (scn_del_copies_of(main_group, target))
			return (rt_err("Cannot delete copies of object"));
		return (0);
	}
	target_grp = &(target->content.group);
	i = 0;
	while (i < target_grp->child_num)
	{
		if (scn_del_copies_rec(main_group, grp->children[i]))
			return (rt_err("Cannot delete copies of object"));
		i++;
	}
	return (0);
}

int				scn_remove_by_name_grp(t_scn *scn, char *name)
{
	t_obj		*grp;

	if (scn == NULL || name == NULL)
		return (rt_err("scn_remove_by_name_grp(): was given a NULL pointer"));
	if ((grp = scn_get_obj_by_name(scn, name)) == NULL)
		return (rt_err("scn_remove_by_name_grp(): obj with given name does not exist"));
	if (grp->type != OBJ_GROUP)
		return (rt_err("scn_remove_by_name_grp(): obj with given name is not a group"));
	//1) remove all copies
	if (scn_del_copies_rec(scn->main_group, grp))
		return (rt_err("cannot delete all copies"));
	//2) deinit group
	if (grp_deinit(grp))
		return (rt_err("Cannot deinit group"));
	return (0);
}
