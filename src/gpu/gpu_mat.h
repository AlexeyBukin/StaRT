/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_mat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:27:49 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_MAT_H
# define GPU_MAT_H

# include "gpu_objects.h"
# include "obj_types.h"
# include "vlk.h"
# include "mtl.h"

typedef struct				s_gpu_mat_pbr
{
	t_vec3					albedo;
	t_vec3					f0;
	t_num					metalness;
	t_num					roughness;
	t_num					transparency;
	t_num					ior;
	int 					albedo_txr_index;
	int 					f0_txr_index;
	int 					metalness_txr_index;
	int 					roughness_txr_index;
	int 					transparency_txr_index;
	int 					normal_txr_index;
}							t_gpu_mat_pbr;

typedef union				u_gpu_mat_content
{
	t_gpu_mat_pbr			pbr;
}							t_gpu_mat_content;

typedef struct				s_gpu_mat
{
	t_id					id;
	t_mat_type				type;
	t_gpu_mat_content		content;
}							t_gpu_mat;

#endif