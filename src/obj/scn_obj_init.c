/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_obj_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 21:32:27 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RT_ID_DEFAULT_MATERIAL 0

#include "rt.h"

int		obj_init(t_obj **dest, t_scn *scn, t_obj_type type)
{
	t_obj		*obj;

	if (dest == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((obj = ft_memalloc(sizeof(t_obj))) == NULL)
		return (rt_err("Cannot create object"));
	obj->id = scn_id();
//	obj->material = scn_get_mat_by_id(DEFAULT_MATERIAL_ID);
	obj->name = NULL;
	tfm_init(&(obj->transform));
	(void)type;
//	if (scn_obj_shape_default(obj, type))
//	{
//		ft_free(obj);
//		return (rt_err("Cannot set default shape"));
//	}
	*dest = obj;
	return (0);
}

int		obj_shape_default(t_obj *obj, t_shp_type type)
{
	int		res;

	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	res = 0;
	(void)type;
//	if (type == SHP_PLANE)
//		res = obj_plane_default(obj);
//	else if (type == SHP_SPHERE)
//		res = obj_sphere_default(obj);
//	else if (type == SHP_CYLINDER)
//		res = obj_cylinder_default(obj);
//	else if (type == SHP_CONE)
//		res = obj_cone_default(obj);
//	else
//		res = rt_err("Unknown object type");
	return (res);
}

//int		obj_transform_default(t_obj *obj)
//{
//	if (obj == NULL)
//		return (rt_err("Given pointer is NULL"));
//	obj->transform.pos_local = vec3(0, 0, 0);
//	obj->transform.pos_global = vec3(0, 0, 0);
//	obj->transform.rot_local = mat3x3_identity();
//	obj->transform.rot_global = mat3x3_identity();
//	return (0);
//}
