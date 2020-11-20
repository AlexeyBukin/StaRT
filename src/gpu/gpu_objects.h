/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_objects.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:41:44 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 04:49:31 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_OBJECTS_H
# define GPU_OBJECTS_H

# include "scn_types.h"

//enum e_obj_type
//{
//	OBJ_NONE = 0,
//	OBJ_PLANE,
//	OBJ_SPHERE,
//	OBJ_CYLINDER,
//	OBJ_CONE,
//	OBJ_GEOMETRY
//};

typedef struct			s_gpu_sphere
{
	t_vec3				pos;
	t_num				r;
}						t_sphere;

typedef struct			s_gpu_plane
{
	t_vec3				n;
	t_num				d;
}						t_plane;

typedef	struct			s_gpu_cone
{
	t_vec3				pos;
	t_vec3				cap;
	t_num				r;
}						t_cone;

typedef	struct			s_gpu_cylinder
{
	t_vec3				pos;
	t_vec3				cap;
	t_num				r;
}						t_cylinder;

typedef union			u_gpu_shape
{
	struct s_gpu_sphere		sphere;
	struct s_gpu_plane		plane;
	struct s_gpu_cone		cone;
	struct s_gpu_cylinder	cylinder;
}						t_gpu_shape;

typedef struct			s_gpu_obj
{
	t_id				id;
	t_id				mat_index;
	t_shp_type			type;
	t_gpu_shape			shape;
	// texture mapping
}						t_gpu_obj;

#endif
