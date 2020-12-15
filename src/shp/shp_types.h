/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shp_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHP_TYPES_H
# define SHP_TYPES_H

# include "tfm_types.h"

typedef enum				e_shp_type
{
	SHP_NONE,
	SHP_PLANE,
	SHP_SPHERE,
	SHP_CYLINDER,
	SHP_CONE,
	SHP_TORUS
//	SHP_MODEL
}							t_shp_type;

// TODO: plane that really a disk??
// eg if radius > 0 then it is a disk?

typedef struct				s_shp_plane
{
	t_num					radius;
}							t_shp_plane;

typedef struct				s_shp_sphere
{
	t_num					radius;
}							t_shp_sphere;

typedef struct				s_shp_cylinder
{
	t_num					length;
	t_num					radius;
}							t_shp_cylinder;

typedef struct				s_shp_cone
{
	t_num					length;
	t_num					radius;
}							t_shp_cone;

typedef union				s_obj_shape
{
	t_shp_plane				plane;
	t_shp_sphere			sphere;
	t_shp_cylinder			cylinder;
	t_shp_cone				cone;
//	t_shp_model				model;
}							t_shp;

#endif
