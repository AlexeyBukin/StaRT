/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_TYPES_H
# define GPU_TYPES_H

//# include "rt_types.h"
# include "gpu_objects.h"
# include "gpu_mat.h"
# include "obj_types.h"
# include "vlk.h"
# include "mtl.h"

typedef union		u_gpu_device
{
	t_mtl			*mtl;
	t_vlk			*vlk;
}					t_gpu_dev;

typedef struct		s_gpu_cam
{
	t_vec3			pos;
	t_mat3x3		rot_axis;
	t_vec2			fov;
}					t_gpu_cam;

typedef struct		s_gpu_info
{
	size_t			obj_num;
	size_t			mat_num;
	size_t			txr_num;
	size_t			render_size;
	size_t			render_square_num;
	size_t			render_square_current;
	t_gpu_cam		camera;
}					t_gpu_info;

typedef struct		s_gpu
{
	t_gpu_dev		dev;
	t_gpu_obj		*obj_buf;
	t_gpu_mat		*mat_buf;
	t_gpu_info		info;
	size_t			obj_current;
	t_txr			*render_result;
}					t_gpu;

#endif
