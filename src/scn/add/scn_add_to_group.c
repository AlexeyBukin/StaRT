/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_to_group.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				scn_add_to_group(t_scn *scn, t_obj *dest, t_obj *obj)
{
	if (scn == NULL || dest == NULL || obj == NULL)
		return (rt_err("scn_add_to_group(): Given pointer is NULL"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group(): dest is not a group"));
	if (obj->type == OBJ_COPY)
		return (scn_add_to_group_copy(scn, dest, obj));
	if (obj->type == OBJ_GROUP)
		return (scn_add_to_group_grp(scn, dest, obj));
	if (obj->type == OBJ_CONTAINER)
		return (scn_add_to_group_obj(scn, dest, obj));
	if (obj->type == OBJ_LIGHT)
		return (scn_add_to_group_lgt(scn, dest, obj));
	if (obj->type == OBJ_CAMERA)
		return (scn_add_to_group_cam(scn, dest, obj));
	return (0);
}
