/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_add_to_group_cam(t_scn *scn, t_obj *dest, t_obj *cam)
{
	if (scn == NULL || dest == NULL || cam == NULL)
		return (rt_err("scn_add_to_group_cam(): Given pointer is NULL"));
	if (cam->type != OBJ_CAMERA)
		return (rt_err("scn_add_to_group_cam(): given obj is not a cam"));
	if (dest->type != OBJ_GROUP)
		return (rt_err("scn_add_to_group_cam(): dest is not a group"));
	if ((scn_name_check(scn, cam->name)))
		return (rt_err("scn_add_to_group_cam(): id collision"));
	if (scn_group_inc(&dest->content.group))
		return (rt_err(""));
	dest->content.group.children[dest->content.group.child_num - 1] = cam;
	cam->parent = dest;
	cam->transform.parent = &(dest->transform);
	return (0);
}
