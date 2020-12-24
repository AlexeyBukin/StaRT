/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_copy_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 20:32:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				obj_copy_init(t_obj **dest, char *name)
{
	t_obj		*copy;

	if (name == NULL || dest == NULL)
		return (rt_err("Given pointer is NULL"));
	copy = ft_memalloc(sizeof(t_obj));
	if (copy == NULL)
		return (rt_err("Cannot malloc object copy"));
	copy->id = scn_id();
	copy->name = name;
	copy->parent = NULL;
	copy->visible = TRUE;
	copy->type = OBJ_COPY;
	copy->content.copy = NULL;
	tfm_init(&(copy->transform));
	copy->transform.parent = NULL;
	*dest = copy;
	return (0);
}

int				obj_copy_deinit(t_obj *copy)
{
	if (copy == NULL)
		return (rt_err("Given pointer is NULL"));
	if (copy->type != OBJ_COPY)
		return (rt_err("Cannot deinit object: not a copy"));
	ft_free(copy->name);
	ft_free(copy);
	return (0);
}
