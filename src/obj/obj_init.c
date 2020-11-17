/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 21:32:27 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			obj_init(t_obj **dest, char *name, t_obj_type type)
{
	if (dest == NULL || name == NULL)
		return (rt_err("Given pointer is NULL"));
	if (type == OBJ_GROUP)
		return (obj_grp_init(dest, name));
	if (type == OBJ_CONTAINER)
		return (obj_container_init(dest, name));
	if (type == OBJ_COPY)
		return (obj_copy_init(dest, name));
	return (rt_err("Unknown object type"));
}

int			obj_deinit(t_obj *obj)
{
	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type == OBJ_GROUP)
		return (obj_grp_deinit(obj));
	if (obj->type == OBJ_CONTAINER)
		return (obj_container_deinit(obj));
	if (obj->type == OBJ_COPY)
		return (obj_copy_deinit(obj));
	return (rt_err("Unknown object type"));
}
