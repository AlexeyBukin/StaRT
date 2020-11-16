/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:29:23 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT_TYPES_H
# define MAT_TYPES_H

# include "libnum.h"
# include "txr_types.h"

typedef struct				s_mat_pbr
{
	t_vec3					albedo;
	t_vec3					f0;
	t_num					metalness;
	t_num					roughness;
	t_num					transparency;
	t_num					ior;
	t_txr					*map_albedo;
	t_txr					*map_f0;
	t_txr					*map_metalness;
	t_txr					*map_roughness;
	t_txr					*map_transparency;
	t_txr					*map_normal;
}							t_mat_pbr;

//typedef struct				s_mat_toon
//{
//	t_vec3					color;
//	t_txr					*map_color;
//	t_vec					shadow_edge;
//	t_vec					shine_edge;
//	t_txr					*map_color;
//	t_num					value;
//}							t_mat_toon;

typedef struct				s_mat_emission
{
	t_vec3					color;
	t_txr					*map_color;
	t_num					value;
}							t_mat_emission;

typedef enum				s_mat_type
{
	MAT_NONE,
	MAT_PBR,
	MAT_EMISSION,
	//RT_MAT_TOON
}							t_mat_type;

typedef union				s_mat_content
{
	t_mat_pbr				pbr;
	t_mat_emission			emission;
//	t_mat_toon				toon;
}							t_mat_content;

typedef struct				s_mat
{
	t_id					id;
	char 					*name;
	t_mat_type				type;
	t_mat_content			content;
	t_vec2					maps_pos;
	t_num					maps_rot;
	t_vec2					maps_scale;
}							t_mat;

#endif
