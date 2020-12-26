/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:40:27 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				gpu_buffer_object_link_material(t_gpu *gpu)
{
	int			obj_i;
	int			mat_i;

	if (gpu == NULL)
		return (rt_err("gpu is NULL"));
	if (gpu->mat_buf == NULL || gpu->obj_buf == NULL)
		return (rt_err("arguments are NULL"));
	obj_i = 0;
	while (obj_i < gpu->info.obj_num)
	{
		mat_i = 0;
		ft_printf("Searching mat with index %d\n",
								gpu->obj_buf[obj_i].mat_index);
		while (mat_i < gpu->info.mat_num
		&& (int)gpu->mat_buf[mat_i].id != gpu->obj_buf[obj_i].mat_index)
		{
			ft_printf(", %d", (int)gpu->mat_buf[mat_i].id);
			mat_i++;
		}
		ft_printf("\n");
		gpu->obj_buf[obj_i].mat_index = mat_i;
		obj_i++;
	}
	return (0);
}

/*
** TODO transform apply
*/

int				gpu_buffer_objects_fill_rec(t_gpu *gpu, t_obj *obj,
										t_tfm *global)
{
	size_t		i;

	if (gpu == NULL || obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (tfm_apply_from_to(global, &obj->transform))
		return (rt_err("Cannot apply transform"));
	if (obj->type == OBJ_CONTAINER)
		return (gpu_buffer_object_container(gpu, obj));
	if (obj->type == OBJ_COPY)
	{
		return (gpu_buffer_objects_fill_rec(gpu,
					obj->content.copy, &obj->transform));
	}
	if (obj->type == OBJ_GROUP)
	{
		i = 0;
		while (i < obj->content.group.child_num)
		{
			if (gpu_buffer_objects_fill_rec(gpu, obj->content.group.children[i],
								&obj->transform))
				return (rt_err("Cannot fill objects"));
			i++;
		}
	}
	return (0);
}

/*
** before loading objects you must load materials!
*/

int				gpu_buffer_objects_init(t_gpu *gpu, t_scn *scn)
{
	int		obj_num;

	if (gpu == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((obj_num = scn_get_num_of(scn, OBJ_CONTAINER)) < 0)
		return (rt_err("Cannot get object num"));
	if ((gpu->info.obj_num = obj_num) == 0)
		return (rt_warn("Scene is empty"));
	if ((gpu->obj_buf = ft_malloc(sizeof(t_gpu_obj)
			* gpu->info.obj_num)) == NULL)
		return (rt_err("Cannot init object buffer"));
	gpu->obj_current = 0;
	if (gpu_buffer_objects_fill_rec(gpu, scn->main_group, NULL))
	{
		ft_free(gpu->obj_buf);
		gpu->obj_buf = NULL;
		gpu->info.obj_num = 0;
		return (rt_err("Cannot init object buffer"));
	}
	if (gpu_buffer_object_link_material(gpu))
		return (rt_err("Cannot link materials"));
	return (0);
}

static int		gpu_buffer_object_container_dop(t_vec3 tmp, t_gpu_obj *gpu_obj,
													t_obj *obj, t_gpu *gpu)
{
	if (gpu_obj->type == SHP_CYLINDER)
	{
		tmp = vec3_normalize(obj->transform.rot_global.z);
		tmp = vec3_mult_num(tmp,
				obj->content.container.shape.cylinder.length / 2);
		gpu_obj->shape.cylinder.pos = vec3_plus(obj->transform.pos_global,
											tmp);
		gpu_obj->shape.cylinder.cap = vec3_minus(obj->transform.pos_global,
											tmp);
		gpu_obj->shape.cylinder.r =
					obj->content.container.shape.cylinder.radius;
	}
	else if (gpu_obj->type == SHP_CONE)
	{
		tmp = vec3_normalize(obj->transform.rot_global.z);
		tmp = vec3_mult_num(tmp,
					obj->content.container.shape.cone.length / 2);
		gpu_obj->shape.cone.pos = vec3_plus(obj->transform.pos_global, tmp);
		gpu_obj->shape.cone.cap = vec3_minus(obj->transform.pos_global, tmp);
		gpu_obj->shape.cone.r = obj->content.container.shape.cone.radius;
	}
	else
		return (rt_err("Unknown object shape type"));
	gpu->obj_current++;
	return (0);
}

int				gpu_buffer_object_container(t_gpu *gpu, t_obj *obj)
{
	t_gpu_obj	*gpu_obj;

	if (gpu == NULL || obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (obj->type != OBJ_CONTAINER)
		return (rt_err("Object is not container"));
	gpu_obj = &(gpu->obj_buf[gpu->obj_current]);
	gpu_obj->id = obj->id;
	gpu_obj->type = obj->content.container.shape_type;
	gpu_obj->map_axis = obj->transform.rot_global;
	gpu_obj->mat_index = obj->content.container.material->id;
	ft_printf("cur pos is %llu, mat_index is %d, name: %s\n",
		gpu->obj_current, gpu_obj->mat_index, obj->name);
	if (gpu_obj->type == SHP_PLANE)
	{
		gpu_obj->shape.plane.d = vec3_len(obj->transform.pos_global);
		gpu_obj->shape.plane.n = obj->transform.rot_global.z;
	}
	else if (gpu_obj->type == SHP_SPHERE)
	{
		gpu_obj->shape.sphere.pos = obj->transform.pos_global;
		gpu_obj->shape.sphere.r = obj->content.container.shape.sphere.radius;
	}
	return (gpu_buffer_object_container_dop(vec3(0, 0, 0), gpu_obj, obj, gpu));
}
