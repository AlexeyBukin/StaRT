/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			scn_add_obj(t_scn *scn, t_obj *obj)
{
	if (scn == NULL || obj == NULL)
		return (rt_err("scn_add_obj(): was given a NULL pointer"));
	if (obj->type == OBJ_COPY)
		return (scn_add_to_group_copy(scn, scn->main_group, obj));
	if (obj->type == OBJ_CONTAINER)
		return (scn_add_to_group_obj(scn, scn->main_group, obj));
	if (obj->type == OBJ_GROUP)
		return (scn_add_to_group_grp(scn, scn->main_group, obj));
	return (rt_err("scn_add_obj(): can\'t recognise object type"));
}
