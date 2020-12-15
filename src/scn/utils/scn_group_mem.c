/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_group_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_group_inc(t_obj_group *grp)
{
	t_obj			**children;

	if (grp->child_num == 0)
	{
		grp->children = (t_obj **)ft_memalloc(sizeof(t_obj *));
		grp->child_num++;
		return (0);
	}
	children = (t_obj **)ft_realloc(grp->children,
									sizeof(t_obj *) * grp->child_num,
									sizeof(t_obj *) * (grp->child_num + 1));
	if (!children)
		return (rt_err("scn_add_to_group_obj():"
		" malloc returned NULL pointer"));
	grp->children = children;
	grp->child_num++;
	return (0);
}
