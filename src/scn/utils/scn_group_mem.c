//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"

int		scn_group_inc(t_obj_group *grp)
{
	t_obj			**children;

	if (grp->child_num == 0)
	{
		grp->children = (t_obj **)ft_memalloc(sizeof(t_obj *));
		grp->child_num++;
		return (0);
	}
	children = (t_obj **)ft_realloc(grp->children,
									sizeof(t_obj *) * grp->child_num,
									sizeof(t_obj *) * (grp->child_num + 1));
	if (!children)
		return (rt_err("scn_add_to_group_obj():"
					   " malloc returned NULL pointer"));
	grp->children = children;
	grp->child_num++;
	return (0);
}
