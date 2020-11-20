//
// Created by Hugor Chau on 11/18/20.
//

# include "rt.h"

int			scn_del_copies_of(t_obj *from, t_obj *original)
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
			if ((grp_remove_by_name(grp->children[i]->parent, grp->children[i]->name) == -1))//TODO make remove_by_id_obj
				return (rt_err("scn_del_copies_of(): couldn' delete copy"));
		}
		else if (grp->children[i]->type == OBJ_GROUP)
		{
			if (scn_del_copies_of(grp->children[i], original))
				return (rt_err("scn_del_copies_of(): couldn' delete copy"));
		}
		i++;
	}
	return (0);
}
