//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"

int				del_obj(t_obj *obj)//t_obj *parent, name
{
	t_obj			**children;
	t_obj_group 	*parent;

	if (!(obj->parent))
		return (rt_err("scn_remove_by_name_copy():"
					   " obj has no parent"));
	parent = &obj->parent->content.group;
//	if (obj->parent->group->type != OBJ_GROUP)
//
	children = (t_obj **)ft_memalloc(sizeof(t_obj *)
									 * (parent->child_num - 1));
	if (!children)
		return (rt_err("scn_remove_by_name_copy():"
					   " malloc returned NULL pointer"));
	grp_memmove(parent, children, obj);
	ft_free(parent->children);
	parent->children = children;
	parent->child_num--;
	return (0);
}

//int			del_obj_copies(t_obj *from, t_obj *original)
int			del_obj_copies(t_obj *from, t_obj *original)
{
	t_obj_group		*grp;
	size_t			i;

	if (from == NULL || original == NULL)
		return (rt_err("fucking NULL"));
	grp = &(from->content.group);
	i = 0;
	while (i < grp->child_num)
	{
		if (grp->children[i]->type == OBJ_COPY
			&& grp->children[i]->content.copy == original)
		{
			if ((delete_copy(grp->children[i]) == -1))//TODO make remove_by_id_obj
				return (rt_err("del_obj_copies(): couldn' delete copy"));
		}
		else if (grp->children[i]->type == OBJ_GROUP)
		{
			if (del_obj_copies(grp->children[i], original))
				return (rt_err("del_obj_copies(): couldn' delete copy"));
		}
		i++;
	}
	return (0);
}

int				scn_remove_by_name_obj(t_scn *scn, char *name)
{
	t_obj		*obj;

	if (!scn || !name)
		return (rt_err("scn_remove_by_name_copy(): was given a NULL pointer"));
	if (!(obj = scn_get_obj_by_name(scn, name)))
		return (rt_err("scn_remove_by_name_copy(): obj with given name does not exist"));
	if (obj->type != OBJ_CONTAINER)
		return (rt_err("scn_remove_by_name_copy(): obj with given name is not an object"));
	if (del_obj_copies(scn->main_group, obj))
		return (rt_err("scn_remove_by_name_copy():"
				" del_obj_copies(): couldn't delete copies"));
	return (scn_remove_from_group_by_name_obj(obj->parent, obj->name)); //obj->id
}
