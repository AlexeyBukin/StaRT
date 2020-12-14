/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_remove_by_name_copy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:03:36 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				scn_remove_by_name_copy(t_scn *scn, char *name)
{
	t_obj		*obj;

	if (!scn || !name)
		return (rt_err("scn_remove_by_name_copy(): was given a NULL pointer"));
	if (!(obj = scn_get_obj_by_name(scn, name)))
		return (rt_err("scn_remove_by_name_copy(): "
		"obj with given name does not exist"));
	if (obj->type != OBJ_COPY)
		return (rt_err("scn_remove_by_name_copy(): "
		"obj with given name is not a copy"));
	if (grp_remove_by_name(obj->parent, name))
		return (rt_err("scn_remove_by_name_copy(): couldn't delete copy"));
	return (obj_deinit(obj));
}
