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

int		scn_obj_plane_default(t_obj *obj)
{
	int			res;

	if (obj == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((obj = ft_memalloc(sizeof(t_obj))) == NULL)
		return (rt_err("Cannot create object"));
	obj->id = scn_id_next();
	obj->material_id = 0;
	if (type == OBJ_PLANE)
		res = scn_obj_plane_default();
	else if (type == OBJ_SPHERE)
		res = scn_obj_sphere_default();
	else if (type == OBJ_CYLINDER)
		res = scn_obj_cylinder_default();
	else if (type == OBJ_CONE)
		res = scn_obj_cone_default();
	else
		res = rt_err("Unknown object type");
	if (res)
	{
		ft_free(obj);
		return (rt_err("Cannot set default object"));
	}
	return (0);
}
