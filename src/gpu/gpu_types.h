/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:28:52 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_TYPES_H
# define GPU_TYPES_H

# include "mtl.h"
# include "vlk.h"
# include "libnum.h"
# include "gpu_objects.h"
# include "gpu_mat.h"

typedef union		u_gpu
{
	t_mtl			*mtl;
	t_vlk			*vlk;
}					t_gpu_dev;

typedef struct		s_gpu_cam
{
	size_t			id;
	t_vec3			pos;
	t_mat3x3		rot_axis;
	t_vec2			fov;
}					t_gpu_cam;

typedef struct		s_gpu_info
{
	int				obj_num;
	int				mat_num;
	int				txr_num;
	int				light_num;
	int				sampling_num;
	int				render_size;
	int				render_square_num;
	int				render_square_current;
	t_gpu_cam		camera;
}					t_gpu_info;

typedef struct		s_gpu
{
	t_gpu_dev		dev;
	t_gpu_obj		*obj_buf;
	t_gpu_mat		*mat_buf;
	t_gpu_light		*lig_buf;
	t_gpu_info		info;
	size_t			obj_current;
	t_txr			*render_result;
}					t_gpu;

#endif
