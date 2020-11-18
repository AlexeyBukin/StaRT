/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_grp_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 20:32:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				grp_swap_with_last_by_name(t_obj *from, char *name)
{
	size_t i;
	t_obj_group *grp;
	t_obj *tmp;

	if (from == NULL || name == NULL)
		return (rt_err("Given pointer is NULL"));
	grp = &(from->content.group);
	i = 0;
	while (i < grp->child_num)
	{
		if (ft_strequ(grp->children[i]->name, name))
			break;
		i++;
	}
	if (i >= grp->child_num)
		return (rt_err("scn_remove_by_name_copy(): obj with given name does not exist"));
	tmp = grp->children[i];
	grp->children[i] = grp->children[grp->child_num - 1];
	grp->children[grp->child_num - 1] = tmp;
	return (0);
}

int				grp_remove_by_name(t_obj *from, char *name)
{
	t_obj			**tmp;
	t_obj_group		*grp;

	if (grp_swap_with_last_by_name(from, name))
		return (rt_err("grp_remove_by_name(): cannot swap with last"));
	grp = &(from->content.group);
	obj_deinit(grp->children[grp->child_num - 1]);
	if (grp->child_num == 1)
	{
		ft_free(grp->children);
		grp->children = NULL;
	}
	else
	{
		tmp = ft_realloc(grp->children,
						 sizeof(t_obj*) * grp->child_num,
						 sizeof(t_obj*) * (grp->child_num - 1));
		if (tmp == NULL)
			return (rt_err("malloc error"));
		grp->children = tmp;
	}
	grp->child_num--;
	return (0);
}
