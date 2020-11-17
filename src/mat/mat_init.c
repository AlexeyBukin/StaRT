/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:48:30 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/16 22:32:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				mat_init_pbr(t_mat_pbr *pbr)
{
	if (pbr == NULL)
		return(rt_err("NULL pointer at mat pbr"));
	pbr->albedo = vec3(0.5, 0.5, 0.5);
	pbr->f0 = vec3(0.05, 0.05, 0.05);
	pbr->metalness = 0;
	pbr->roughness = 0.5;
	pbr->transparency = 0;
	pbr->ior = 1.2;
	pbr->map_albedo = NULL;
	pbr->map_f0 = NULL;
	pbr->map_metalness = NULL;
	pbr->map_normal = NULL;
	pbr->map_roughness = NULL;
	pbr->map_transparency = NULL;
	return(0);
}

int				mat_init_default(t_mat **mat_container)
{
	t_mat		*mat;
	
	if (mat_init(&mat, ft_strdup(DEFAULT_MATERIAL_NAME)))
		return (rt_err("can't init material"));
	mat->type = MAT_PBR;
	mat_init_pbr(&(mat->content.pbr));
	mat->maps_rot = (t_num)0.5;
	mat->id = DEFAULT_MATERIAL_ID;
	*mat_container = mat;
	return (0);
}

int             mat_init(t_mat **mat_container, char *mat_name)
{
	t_mat		*mat;
	
	if (mat_container == NULL || mat_name == NULL)
		return (rt_err("mat_init(): mat_container is NULL pointer"));
//	if (scn_name_check(scn, mat_name))
//		return (rt_err("mat name is already used, try another"));
	if ((mat = ft_memalloc(sizeof(t_mat))) == NULL)
		return (rt_err("mat_init(): malloc returned NULL pointer"));
    mat->id = scn_id();
	mat->name = mat_name;
	mat->type = MAT_NONE;
	// mat->content = NULL;
	mat->maps_pos = vec2_zero();
	mat->maps_rot = (t_num)0;
	mat->maps_scale = vec2(1, 1);
	*mat_container = mat;
	return(0);
}

int				mat_deinit(t_mat *mat)
{
	if (mat == NULL)
		return (rt_err("NULL pointer at mat deinint"));
	ft_free(mat->name);
	ft_free(mat);
	return (0);
}
