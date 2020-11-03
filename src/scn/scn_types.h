/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/03 23:15:17 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_TYPES_H
# define SCN_TYPES_H

# include "scn_objects.h"

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
