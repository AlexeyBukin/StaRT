/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_to_group_lgt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_add_to_group_lgt(t_scn *scn, t_obj *dest, t_obj *lgt)
{
	if (scn == NULL || dest == NULL || lgt == NULL)
		return (rt_err("scn_add_to_group_lgt(): given NULL pointer"));
	if (lgt->type != OBJ_LIGHT)
		return (rt_err("scn_add_to_group_lgt(): given obj is not a light"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_lgt(): dest is not a group"));
	if ((scn_name_check(scn, lgt->name)))
		return (rt_err("scn_add_to_group_lgt(): name collision"));
	if (scn_group_inc(&dest->content.group))
		return (rt_err("scn_add_to_group_lgt(): malloc error"));
	dest->content.group.children[dest->content.group.child_num - 1] = lgt;
	lgt->parent = dest;
	lgt->transform.parent = &(dest->transform);
	return (0);
}
