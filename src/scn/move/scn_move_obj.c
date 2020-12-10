/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_move_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_is_cycled_rec(t_obj *dst, t_obj *obj)
{
	if (dst->parent == NULL)
		return (0);
	if (dst->parent == obj)
		return (-1);
	return (scn_is_cycled_rec(dst->parent, obj));
}

int		scn_move_obj(t_scn *scn, t_obj *dst, t_obj *obj)
{
	if (scn == NULL || obj == NULL)
		return (rt_err("scn_move_obj(): given NULL pointer"));
	if (dst == NULL)
		return (0);
	if (dst->type != OBJ_GROUP)
		return (rt_err("scn_move_obj(): destination is not group"));
	if (dst == obj)
		return (rt_err("can\'t move object to itself"));
	if (dst == obj->parent)
		return (rt_err("can\'t move object to it\'s parent"));
	if (scn_is_cycled_rec(dst, obj))
		return (rt_err("detected cycle"));
	if (dst != (scn_get_obj_by_name(scn, dst->name)))
		return (rt_err("scn_move_obj(): couldn\'t find given group in scene"));
	if (obj != (scn_get_obj_by_name(scn, obj->name)))
		return (rt_err("scn_move_obj(): couldn\'t find given obj in scene"));
	if (grp_remove_by_name(obj->parent, obj->name))
		return (rt_err("scn_move_obj(): couldn\'t remove obj from group"));
	if (scn_add_to_group(scn, dst, obj))
		return (rt_err("scn_move_obj(): couldn\'t add obj to group"));
	return (0);
}
