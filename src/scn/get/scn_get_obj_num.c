/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_obj_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					scn_get_obj_num_rec(t_obj *obj)
{
	int				tmp;
	int				res;
	size_t			i;

	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type == OBJ_CONTAINER)
		return (1);
	if (obj->type == OBJ_COPY)
		return (scn_get_obj_num_rec(obj->content.copy));
	if (obj->type == OBJ_GROUP)
	{
		res = 0;
		i = 0;
		while (i < obj->content.group.child_num)
		{
			tmp = scn_get_obj_num_rec(obj->content.group.children[i]);
			if (tmp < 0)
				return (tmp);
			res += tmp;
			i++;
		}
		return (res);
	}
	return (rt_err("Unknown object type"));
}

int					scn_get_obj_num(t_scn *scn)
{
	if (scn == NULL)
		return (rt_err("Given pointer is NULL"));
	return (scn_get_obj_num_rec(scn->main_group));
}
