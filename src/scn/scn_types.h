/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_TYPES_H
# define SCN_TYPES_H

# include "scn_objects.h"
#include "scn_map.h"
# define SIZE_STEP 16

typedef struct		s_cam
{
	uint			id;
	char			*name;
	t_vec3			pos;
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
	t_vec2			fov;
}					t_cam;

typedef union		u_mat_param
{
	uint			map_id;
	t_num 			value;
}					t_mat_param;

typedef union		u_mat_param3
{
	uint			map_id;
	t_vec3 			value;
}					t_mat_param3;

typedef struct				s_mat
{
	uint			id;
	char			*name;
	t_mat_param		metalness;
	t_mat_param		roughness;
	t_mat_param		ior;
	t_mat_param		transparency;
	t_mat_param3	albedo;
	t_mat_param3	f0;
}							t_mat;

typedef union		u_component
{
	t_obj			obj;
	t_mat			mat;
	t_mat			cam;
	// textures, groups, etc
}					t_component;

enum e_comp_type
{
	COMPONENT_ANY = -1,
	COMPONENT_NONE,
	COMPONENT_OBJECT,
	COMPONENT_MATERIAL,
	COMPONENT_TEXTURE,
	COMPONENT_CAMERA,
	COMPONENT_NUM
};

typedef struct		s_scn
{
	char				*name;
	struct s_obj		*objects;
	uint				objects_num;
	uint				objects_max;
	struct s_mat		*materials;
	uint				materials_num;
	uint				materials_max;
	struct s_cam		camera;
	struct s_cam		*cameras;
	uint				cameras_num;
	uint				cameras_max;
	t_map				id_to_name;
	t_hash_map			name_to_id;
//	t_map				*id_to_name;
//	t_hash_map			*name_to_id;
}					t_scn;

typedef enum		e_scn_shape_type
{
	SCN_SHAPE_NONE = 0,
	SCN_SHAPE_PLANE,
	SCN_SHAPE_SPHERE,
	SCN_SHAPE_CYLINDER,
	SCN_SHAPE_CONE,
	SCN_SHAPE_GEOMETRY
}					t_scn_shape_type;

typedef unsigned int		t_id;

typedef struct				s_scn_group
{
	t_id					id;
	t_scn_transform			transform;
	char					*name;
	struct s_scn_object		*children;
	size_t					child_num;
	size_t					child_max;
}							t_scn_group;

typedef struct				s_scn_object
{
	t_id					id;
	t_scn_transform			transform;
	char					*name;
	t_scn_group				*parent;
	t_scn_shape_type		type;
	t_scn_material			*material;
}							t_scn_object;

typedef struct				s_scn_transform
{
	t_vec3					pos_local;
	t_vec3					pos_global;
	t_mat3x3				rot_origin;
	t_vec3					rot_local;
	t_vec3					rot_global;
}							t_scn_transform;

#endif
