/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rm_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		remove_material_rec(t_obj *obj, t_mat *default_mat, t_mat *mat_to_del)
{
	size_t			i;
	t_obj_group		*grp;

	i = 0;
	if (obj->type == OBJ_COPY)
		return (0);
	if (obj->type == OBJ_CONTAINER)
	{
		if (obj->content.container.material == mat_to_del)
			obj->content.container.material = default_mat;
		return (0);
	}
	if (obj->type != OBJ_GROUP)
		return (rt_err("remove_material_rec(): can\'t identify obj type."));
	grp = &(obj->content.group);
	while (i < grp->child_num)
	{
		if (remove_material_rec(grp->children[i], default_mat, mat_to_del))
			return (rt_err("Cannot delete material"));
		i++;
	}
	return (0);
}

int		cmd_rm_material(t_rt *rt, t_parser *parser)
{
	t_mat		*default_mat;
	t_mat		*mat_to_del;

	if (!(mat_to_del = scn_get_mat_by_name(rt->scene, parser->name)))
		return (rt_err("Cannot delete material"));
	if (!(default_mat = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME)))
		return (rt_err("Cannot delete material"));
	return (remove_material_rec(rt->scene->main_group,
			default_mat, mat_to_del));
}
