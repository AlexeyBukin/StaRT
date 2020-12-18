/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:40:27 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int 			gpu_buffer_lights_init(t_gpu *gpu, t_scn *scn)
{
	int 		lgt_num;

	if (gpu == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((lgt_num = scn_get_num_of(scn, OBJ_LIGHT)) < 0)
		return (rt_err("Cannot get light num"));
	if ((gpu->info.obj_num = lgt_num) == 0)
		return (rt_warn("Scene is empty"));
	if ((gpu->lgt_buf = ft_malloc(sizeof(t_gpu_light) * gpu->info.lgt_num)) == NULL)
		return (rt_err("Cannot init lights buffer"));
	gpu->obj_current = 0;
	if (gpu_buffer_lights_fill_rec(gpu, scn->main_group, NULL))
	{
		ft_free(gpu->lgt_buf);
		gpu->lgt_buf = NULL;
		gpu->info.lgt_num = 0;
		return (rt_err("Cannot fill lights buffer"));
	}
	return (0);
}

/*
** TODO transform apply
*/


int 			gpu_buffer_lights_fill_rec(t_gpu *gpu, t_obj *obj, t_tfm *global)
{
	t_tfm		tfm;
	size_t		i;

	if (gpu == NULL || obj == NULL)
		return (rt_err("Given pointer is NULL"));
    (void)global;
	// if (tfm_apply_from_to(global, &tfm))
	// 	return (rt_err("Cannot apply transform"));
	if (obj->type == OBJ_LIGHT)
		return (gpu_buffer_light_object(gpu, obj, &tfm));
	if (obj->type == OBJ_COPY)
		return (gpu_buffer_lights_fill_rec(gpu, obj->content.copy, &tfm));
	if (obj->type == OBJ_GROUP)
	{
		i = 0;
		while (i < obj->content.group.child_num)
		{
			if (gpu_buffer_lights_fill_rec(gpu, obj->content.group.children[i], &tfm))
				return (rt_err("Cannot fill objects"));
			i++;
		}
	}
	return (0);
}

int				gpu_buffer_light_object(t_gpu *gpu, t_obj *obj, t_tfm *global)
{
	t_gpu_light		*gpu_lgt;

	if (gpu == NULL || obj == NULL || global == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type != OBJ_LIGHT)
		return (rt_err("Object is not light"));
	gpu_lgt = &(gpu->lgt_buf[gpu->obj_current]);
	gpu_lgt->id = obj->id;
	gpu_lgt->pos = global->pos_global;
	gpu_lgt->col = obj->content.light.light.color;
	gpu_lgt->power = obj->content.light.light.intensity;
	return (0);
}
