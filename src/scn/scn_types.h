/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/03 23:50:59 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_TYPES_H
# define SCN_TYPES_H

# include "scn_objects.h"

struct				s_cam
{
	uint			id;
	t_vec3			pos;
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
	t_vec2			fov;
};

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
	t_mat_param		metalness;
	t_mat_param		roughness;
	t_mat_param		ior;
	t_mat_param		transparency;
	t_mat_param3	albedo;
	t_mat_param3	f0;
}							t_mat;

typedef struct		s_scn
{
	uint				id;
	struct s_obj		*objects;
	int					objects_num;
	struct s_mat		*materials;
	int					materials_num;
	struct s_cam		camera;
}					t_scn;

#endif
