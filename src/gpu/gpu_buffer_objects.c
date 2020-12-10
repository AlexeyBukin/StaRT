/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/05 18:45:04 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// must load materials first!

int 			gpu_buffer_objects_init(t_gpu *gpu, t_scn *scn)
{
	int 		obj_num;

	if (gpu == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((obj_num = scn_get_obj_num(scn)) < 0)
		return (rt_err("Cannot get object num"));
	if ((gpu->info.obj_num = obj_num) == 0)
		return (rt_warn("Scene is empty"));
	if ((gpu->obj_buf = ft_malloc(sizeof(t_gpu_obj) * gpu->info.obj_num)) == NULL)
		return (rt_err("Cannot init object buffer"));
	gpu->obj_current = 0;
	if (gpu_buffer_objects_fill_rec(gpu, scn->main_group, NULL))
	{
		ft_free(gpu->obj_buf);
		gpu->info.obj_num = 0;
//		gpu->obj_buf = NULL; // kcharla: maybe we won't quit??
		return (rt_err("Cannot init object buffer"));
	}
	return (0);
}

int 			gpu_buffer_objects_fill_rec(t_gpu *gpu, t_obj *obj, t_tfm *global)
{
	t_tfm		tfm;
	size_t		i;

	if (gpu == NULL || obj == NULL)
		return (rt_err("Given pointer is NULL"));
    (void)global;
	if (tfm_apply_from_to(global, &tfm))
		return (rt_err("Cannot apply transform"));
	if (obj->type == OBJ_CONTAINER)
		return (gpu_buffer_object_container(gpu, obj, &tfm));
	if (obj->type == OBJ_COPY)
		return (gpu_buffer_objects_fill_rec(gpu, obj->content.copy, &tfm));
	if (obj->type == OBJ_GROUP)
	{
		i = 0;
		while (i < obj->content.group.child_num)
		{
			if (gpu_buffer_objects_fill_rec(gpu, obj->content.group.children[i], &tfm))
				return (rt_err("Cannot fill objects"));
			i++;
		}
		return (0);
	}
	return (rt_err("Unknown object type"));
}

int				gpu_buffer_object_container(t_gpu *gpu, t_obj *obj, t_tfm *global)
{
	t_vec3		tmp;
	t_gpu_obj	*gpu_obj;

	if (gpu == NULL || obj == NULL || global == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type != OBJ_CONTAINER)
		return (rt_err("Object is not container"));
	gpu_obj = &(gpu->obj_buf[gpu->obj_current]);
	gpu_obj->type = obj->content.container.shape_type;
	gpu_obj->map_axis = obj->transform.rot_global;
	if (gpu_obj->type == SHP_PLANE)
	{
		//manage inversion of D ??
		gpu_obj->shape.plane.d = vec3_len(global->pos_global);
		gpu_obj->shape.plane.n = global->rot_global.z;
	}
	else if (gpu_obj->type == SHP_SPHERE)
	{
		gpu_obj->shape.sphere.pos = global->pos_global;
		gpu_obj->shape.sphere.r = obj->content.container.shape.sphere.radius;
	}
	else if (gpu_obj->type == SHP_CYLINDER)
	{
		tmp = vec3_normalize(global->rot_global.z);
		tmp = vec3_mult_num(tmp, obj->content.container.shape.cylinder.length / 2);
		gpu_obj->shape.cylinder.pos = vec3_plus(global->pos_global, tmp);
		gpu_obj->shape.cylinder.cap = vec3_minus(global->pos_global, tmp);
		gpu_obj->shape.cylinder.r = obj->content.container.shape.cylinder.radius;
	}
	else if (gpu_obj->type == SHP_CONE)
	{
		tmp = vec3_normalize(global->rot_global.z);
		tmp = vec3_mult_num(tmp, obj->content.container.shape.cone.length / 2);
		gpu_obj->shape.cone.pos = vec3_plus(global->pos_global, tmp);
		gpu_obj->shape.cone.cap = vec3_minus(global->pos_global, tmp);
		gpu_obj->shape.cone.r = obj->content.container.shape.cone.radius;
	}
	else
		return (rt_err("Unknown object type"));
	return (0);
}
