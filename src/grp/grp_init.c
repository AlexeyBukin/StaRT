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

int				grp_init(t_obj **dest, char *name)
{
	t_obj		*grp;

	if (name == NULL || dest == NULL)
		return (rt_err("Given pointer is NULL"));
	grp = ft_memalloc(sizeof(t_obj));
	if (grp == NULL)
		return (rt_err("Cannot malloc group"));
	grp->id = scn_id();
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

int				grp_deinit(t_obj *group)
{
	size_t		i;

	if (group == NULL)
		return (rt_err("Given pointer is NULL"));
	if (group->type != OBJ_GROUP)
		return (rt_err("Cannot deinit object: not a group"));
	i = 0;
	while (i < group->content.group.child_num)
	{
		if (obj_deinit(group->content.group.children[i]))
			return (rt_err("Cannot deinit object"));
		i++;
	}
	if (group->content.group.child_num > 0)
		ft_free(group->content.group.children);
	ft_free(group->name);
	ft_free(group);
	return (0);
}
