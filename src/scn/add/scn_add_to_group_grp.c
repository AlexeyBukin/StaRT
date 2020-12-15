/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_to_group_grp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				scn_add_to_group_grp(t_scn *scn, t_obj *dest, t_obj *grp)
{
	if (scn == NULL || dest == NULL || grp == NULL)
		return (rt_err("scn_add_to_group_grp(): Given pointer is NULL"));
	if (grp->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_grp(): given obj is not a group"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_grp(): dest is not a group"));
	if ((scn_name_check(scn, grp->name)))
		return (rt_err("scn_add_to_group_grp(): name collision"));
	if (scn_group_inc(&dest->content.group))
		return (rt_err(""));
	dest->content.group.children[dest->content.group.child_num - 1] = grp;
	grp->parent = dest;
	grp->transform.parent = &(dest->transform);
	return (0);
}
