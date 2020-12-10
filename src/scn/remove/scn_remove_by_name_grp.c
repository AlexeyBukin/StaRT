/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_remove_by_name_grp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		if (scn_del_copies_rec(main_group, target_grp->children[i]))
			return (rt_err("Cannot delete copies of object"));
		i++;
	}
	scn_del_copies_of(main_group, target);
	return (0);
}

int				scn_remove_by_name_grp(t_scn *scn, char *name)
{
	t_obj		*grp;

	if (scn == NULL || name == NULL)
		return (rt_err("scn_remove_by_name_grp(): was given a NULL pointer"));
	if ((grp = scn_get_obj_by_name(scn, name)) == NULL)
		return (rt_err("scn_remove_by_name_grp(): "
		"obj with given name does not exist"));
	if (grp->type != OBJ_GROUP)
		return (rt_err("scn_remove_by_name_grp(): "
		"obj with given name is not a group"));
	if (scn_del_copies_rec(scn->main_group, grp))
		return (rt_err("cannot delete all copies"));
	if (grp_remove_by_name(grp->parent, grp->name))
		return (rt_err("Cannot remove group"));
	if (grp_deinit(grp))
		return (rt_err("Cannot deinit group"));
	return (0);
}
