/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:26:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 18:28:26 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_H
# define RT_SCENE_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"

typedef float t_num;

typedef struct		s_vec2
{
	t_num			x;
	t_num			y;
}					t_vec2;

typedef struct		s_vec3
{
	t_num			x;
	t_num			y;
	t_num			z;
}					t_vec3;

enum e_obj_type
{
	OBJ_NONE = 0,
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_GEOMETRY
};

struct				s_sphere
{
	t_vec3			pos;
	t_num			r;
};

struct				s_plane
{
	t_vec3			n;
	t_num			d;
};

union				u_shape
{
	struct s_sphere		sphere;
	struct s_plane		plane;
};

typedef struct				s_obj
{
	int						id;
	int						material_id;
	enum e_obj_type			type;
	union u_shape			shape;
}							t_obj;

struct				s_cam
{
	int				id;
	t_vec3			pos;
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
	t_vec2			fov;
};

typedef struct				s_mat
{
	int				id;
	float 			metalness;
	float 			roughness;
	float 			ior;
	float 			transparency;
	t_vec3			albedo;
	t_vec3			f0;
}							t_mat;

typedef struct		s_scn
{
	int					id;
	struct s_obj		*objects;
	int					objects_num;
	struct s_mat		*materials;
	int					materials_num;
	struct s_cam		camera;
}					t_scn;

#endif
