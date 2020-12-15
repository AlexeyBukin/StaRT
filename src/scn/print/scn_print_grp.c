/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_print_grp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:32:23 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		print_children(t_obj *obj, int tab_num)
{
	t_obj_group		grp;
	size_t			i;
	t_obj_type		j;

	grp = obj->content.group;
	write_tabs(tab_num);
	ft_printf("group %s:\n", obj->name);
	j = OBJ_NONE;
	while (j == OBJ_NONE || j == OBJ_CONTAINER || j == OBJ_LIGHT ||
			j == OBJ_COPY || j == OBJ_GROUP || j == OBJ_CAMERA)
	{
		i = 0;
		while (i < grp.child_num)
		{
			if (grp.children[i]->type == j)
			{
				if (scn_print_grp_rec(grp.children[i], tab_num + 1))
					return (rt_err("scn_print_grp_rec(): "
					"couldn\'t get info about obj"));
			}
			i++;
		}
		j++;
	}
	return (0);
}

int		scn_print_grp_rec(t_obj *obj, int tab_num)
{
	if (obj == NULL)
		return (rt_err("scn_print_grp(): obj was given as a NULL pointer"));
	scn_print_obj(obj, tab_num);
	if (obj->type != OBJ_GROUP)
		return (0);
	return (print_children(obj, tab_num));
}

int		scn_print_grps(t_scn *scn)
{
	return (scn_print_grp_rec(scn->main_group, 0));
}
