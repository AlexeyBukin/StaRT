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

enum e_obj_type
{
	OBJ_NONE = 0,
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_GEOMETRY
};

typedef struct			s_sphere
{
	t_vec3				pos;
	t_num				r;
}						t_sphere;

typedef struct			s_plane
{
	t_vec3				n;
	t_num				d;
}						t_plane;

typedef	struct			s_cone
{
	t_vec3				pos;
	t_vec3				cap;
	t_num				r;
}						t_cone;

typedef	struct			s_cylinder
{
	t_vec3				pos;
	t_vec3				cap;
	t_num				r;
}						t_cylinder;

union					u_shape
{
	struct s_sphere		sphere;
	struct s_plane		plane;
	struct s_cone		cone;
	struct s_cylinder	cylinder;
};

typedef struct			s_gpu_obj
{
	t_id				id;
	t_id				material_id;
	enum e_obj_type		type;
	union u_shape		shape;
}						t_gpu_obj;

#endif
