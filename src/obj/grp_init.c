/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 20:32:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			grp_init(t_obj **dest, char *name)
{
	t_obj		*grp;

	if (name == NULL || dest == NULL)
		return (rt_err("Given pointer is NULL"));
	grp = ft_memalloc(sizeof(t_obj));
	if (grp == NULL)
		return (rt_err("Cannot malloc group"));
	grp->name = name;
	grp->parent = NULL;
	grp->visible = TRUE;

	grp->type = OBJ_GROUP;
	grp->content.group.children = NULL;
	grp->content.group.child_num = 0;

	tfm_init(&(grp->transform));
	grp->transform.parent = NULL;

	*dest = grp;
	return (0);
}
