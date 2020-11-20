/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_container_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 20:32:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				obj_container_init(t_obj **dest, char *name)
{
	t_obj		*cont;

	if (name == NULL || dest == NULL)
		return (rt_err("Given pointer is NULL"));
	cont = ft_memalloc(sizeof(t_obj));
	if (cont == NULL)
		return (rt_err("Cannot malloc container object"));

	cont->id = scn_id();
	cont->name = name;
	cont->parent = NULL;
	cont->visible = TRUE;

	cont->type = OBJ_CONTAINER;
	cont->content.container.shape_type = SHP_NONE;
	cont->content.container.material = NULL;

	tfm_init(&(cont->transform));
	cont->transform.parent = NULL;

	*dest = cont;
	return (0);
}

int				obj_container_deinit(t_obj *cont)
{
	if (cont == NULL)
		return (rt_err("Given pointer is NULL"));
	if (cont->type != OBJ_CONTAINER)
		return (rt_err("Cannot deinit object: not a container"));
	ft_free(cont->name);
	ft_free(cont);
	return (0);
}
