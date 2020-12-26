/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_buffer_materials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:40:27 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO init xxx_num in init_info
*/

int				gpu_buffer_materials_init(t_gpu *gpu, t_scn *scn)
{
	size_t		i;

	if (gpu == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	gpu->info.mat_num = scn->materials_num;
	gpu->mat_buf = ft_malloc(sizeof(t_gpu_mat) * gpu->info.mat_num);
	if (gpu->mat_buf == NULL)
		return (rt_err("Cannot create materials buffer"));
	i = 0;
	while (i < (size_t)gpu->info.mat_num)
	{
		if (gpu_buffer_material_pbr(&(gpu->mat_buf[i]), scn->materials[i]))
		{
			ft_free(gpu->mat_buf);
			gpu->mat_buf = NULL;
			gpu->info.mat_num = 0;
			return (rt_err("Cannot fill materials buffer"));
		}
		i++;
	}
	return (0);
}

/*
** TODO add textures references
*/

int				gpu_buffer_material_pbr(t_gpu_mat *gmat, t_mat *smat)
{
	if (gmat == NULL || smat == NULL)
		return (rt_err("Given pointer is NULL"));
	if (smat->type != MAT_PBR)
		return (rt_err("Unknown material type"));
	gmat->id = smat->id;
	gmat->type = smat->type;
	gmat->content.pbr.albedo = smat->content.pbr.albedo;
	gmat->content.pbr.f0 = smat->content.pbr.f0;
	gmat->content.pbr.metalness = smat->content.pbr.metalness;
	gmat->content.pbr.roughness = smat->content.pbr.roughness;
	gmat->content.pbr.transparency = smat->content.pbr.transparency;
	gmat->content.pbr.ior = smat->content.pbr.ior;
	gmat->content.pbr.albedo_txr_index = -1;
	gmat->content.pbr.f0_txr_index = -1;
	gmat->content.pbr.metalness_txr_index = -1;
	gmat->content.pbr.roughness_txr_index = -1;
	gmat->content.pbr.transparency_txr_index = -1;
	gmat->content.pbr.normal_txr_index = -1;
	return (0);
}
