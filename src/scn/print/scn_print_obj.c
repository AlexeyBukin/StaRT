/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_print_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		write_tabs(int tab_num)
{
	while (tab_num)
	{
		ft_printf("\t");
		tab_num--;
	}
}

void		scn_print_obj_common_params(t_tfm *trf)
{
	ft_printf("pos <%.3f, %.3f, %.3f> ",
			trf->pos_local.x, trf->pos_local.y, trf->pos_local.z);
	ft_printf("angle [<%.3f, %.3f, %.3f>, <%.3f, %.3f, %.3f>, "
				"<%.3f, %.3f, %.3f>]\n",
				trf->rot_local.x.x, trf->rot_local.x.y, trf->rot_local.x.z,
				trf->rot_local.y.x, trf->rot_local.y.y, trf->rot_local.y.z,
				trf->rot_local.z.x, trf->rot_local.z.y, trf->rot_local.z.z);
}

void		scn_print_shape(t_obj *obj)
{
	if (obj->type == OBJ_CONTAINER)
	{
		if (obj->content.container.shape_type == SHP_SPHERE)
			ft_printf("shape SPHERE rad %.3f ",
			obj->content.container.shape.sphere.radius);
		else if (obj->content.container.shape_type == SHP_PLANE)
			ft_printf("shape PLANE ");
		else if (obj->content.container.shape_type == SHP_CONE)
			ft_printf("shape CONE rad %.3f len %.3f ",
			obj->content.container.shape.cone.radius,
			obj->content.container.shape.cone.length);
		else if (obj->content.container.shape_type == SHP_CYLINDER)
			ft_printf("shape CYLINDER rad %.3f len %.3f ",
			obj->content.container.shape.cylinder.radius,
			obj->content.container.shape.cylinder.length);
		else
		{
			ft_printf("shape UNKNOWN ");
			return (scn_print_obj_common_params(&obj->transform));
		}
		ft_printf(" material_name %s ", obj->content.container.material->name);
	}
}

int			scn_print_obj(t_obj *obj, int tab_num)
{
	if (obj == NULL)
		return (rt_err("scn_print_obj(): given NULL pointer"));
	write_tabs(tab_num);
	ft_printf("%s id %d %s ", obj->name, obj->id,
			obj->visible == TRUE ? "VISIBLE" : "NOT VISIBLE");
	if (obj->type == OBJ_CONTAINER)
		scn_print_shape(obj);
	if (obj->type == OBJ_LIGHT)
	{
		ft_printf("LIGHT intensity %.3f %s; color <%.3f, %.3f, %.3f> ",
			obj->content.light.light.intensity,
			obj->content.light.lgt_type == LGT_PARALLEL ? "PARALLEL" : "POINT",
			obj->content.light.light.color.x, obj->content.light.light.color.y,
			obj->content.light.light.color.z);
	}
	if (obj->type == OBJ_CAMERA)
	{
		ft_printf("CAMERA fov <%.3f %.3f> ", obj->content.camera.fov.x,
				obj->content.camera.fov.y);
	}
	scn_print_obj_common_params(&obj->transform);
	return (0);
}
