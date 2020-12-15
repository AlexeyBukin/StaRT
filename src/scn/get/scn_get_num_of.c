/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_lgt_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:18:12 by rtacos            #+#    #+#             */
/*   Updated: 2020/12/14 18:18:13 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					scn_get_num_of_rec(t_obj *obj, t_obj_type type)
{
	int				tmp;
	int				res;
	size_t			i;

	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type == type)
		return (1);
	if (obj->type == OBJ_COPY)
		return (scn_get_num_of_rec(obj->content.copy, type));
	if (obj->type == OBJ_GROUP)
	{
		res = 0;
		i = 0;
		while (i < obj->content.group.child_num)
		{
			tmp = scn_get_num_of_rec(obj->content.group.children[i], type);
			if (tmp < 0)
				return (tmp);
			res += tmp;
			i++;
		}
		return (res);
	}
	return (0);
}

int					scn_get_num_of(t_scn *scn, t_obj_type type)
{
	if (scn == NULL)
		return (rt_err("Given pointer is NULL"));
	return (scn_get_num_of_rec(scn->main_group, type));
}