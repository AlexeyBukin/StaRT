//
// Created by Hugor Chau on 11/18/20.
//

#include "rt.h"
//TODO

int		scn_group_inc(t_obj_group *grp)
{
	t_obj			**children;

	children = (t_obj **)ft_realloc(grp->children,
									sizeof(t_obj *) * grp->child_num,
									sizeof(t_obj) * (grp->child_num + 1));
	if (!children)
		return (rt_err("scn_add_to_group_obj():"
					   " malloc returned NULL pointer"));
	ft_free(grp->children);
	grp->children = children;
	grp->child_num++;
	return (0);
}
