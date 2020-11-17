/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_obj_by_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj				*scn_get_obj_by_name_rec(t_obj *grp, char *name)
{
	t_obj			*tmp;
	size_t			i;

	if (grp == NULL || name == NULL)
		return (null(rt_err("Given pointer is NULL")));
	if (ft_strequ(grp->name, name))
		return (grp);
	if (grp->type == OBJ_GROUP)
	{
		i = 0;
		while (i < grp->content.group.child_num)
		{
			tmp = grp->content.group.children[i];
			tmp = scn_get_obj_by_name_rec(tmp, name);
			if (tmp != NULL)
				return (tmp);
			i++;
		}
	}
	return (NULL);
}

t_obj				*scn_get_obj_by_name(t_scn *scn, char *name)
{
	if (name == NULL || scn == NULL)
		return (null(rt_err("Given pointer is NULL")));
	return (scn_get_obj_by_name_rec(scn->main_group, name));
}
