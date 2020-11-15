/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_obj_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:32:03 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 20:32:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RT_ID_DEFAULT_MATERIAL 0

int		scn_obj_init(t_obj **dest, t_scn *scn, t_obj_type type)
{
	int			res;
	t_obj		*obj;

	if (dest == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((obj = ft_memalloc(sizeof(t_obj))) == NULL)
		return (rt_err("Cannot create object"));
	obj->id = scn_id_next();
	obj->material_id = RT_ID_DEFAULT_MATERIAL;
	obj->name = NULL;
	scn_obj_transform_default(obj);
	if (scn_obj_shape_default(obj, type))
	{
		ft_free(obj);
		return (rt_err("Cannot set default shape"));
	}
	return (0);
}

int		scn_obj_shape_default(t_obj *obj, t_obj_type type)
{
	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if (type == OBJ_PLANE)
		res = scn_obj_plane_default(obj);
	else if (type == OBJ_SPHERE)
		res = scn_obj_sphere_default(obj);
	else if (type == OBJ_CYLINDER)
		res = scn_obj_cylinder_default(obj);
	else if (type == OBJ_CONE)
		res = scn_obj_cone_default(obj);
	else
		res = rt_err("Unknown object type");
	return (res);
}

void		scn_obj_transform_default(t_obj *obj)
{
	if (obj == NULL)
		return ;
	obj->pos_local = vec3(0, 0, 0);
	obj->pos_global = vec3(0, 0, 0);
	obj->pos_diff = vec3(0, 0, 0);
	obj->rot_local = mat3x3_identity();
	obj->rot_global = mat3x3_identity();
	obj->rot_diff = mat3x3_identity();
	return (0);
}
