/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_obj_by_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj				*scn_get_obj_by_id_rec(t_obj *grp, t_id id)
{
	t_obj			*tmp;
	size_t			i;

	if (grp == NULL || name == NULL)
		return (null(rt_err("Given pointer is NULL")));
	if (grp->id == id)
		return (grp);
	if (grp->type == OBJ_GROUP)
	{
		i = 0;
		while (i < grp->content.group.child_num)
		{
			tmp = grp->content.group.children[i];
			tmp = scn_get_obj_by_id_rec(tmp, id);
			if (tmp != NULL)
				return (tmp);
			i++;
		}
	}
	return (NULL);
}

t_obj				*scn_get_obj_by_id(t_scn *scn, t_id id)
{
	if (name == NULL || scn == NULL)
		return (null(rt_err("Given pointer is NULL")));
	return (scn_get_obj_by_id_rec(scn->main_group, id));
}
