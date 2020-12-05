/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_TYPES_H
# define OBJ_TYPES_H

# include "tfm_types.h"
# include "shp_types.h"
# include "mat_types.h"
# include "lgt_types.h"
# include "libft.h"

typedef enum				s_obj_type
{
	OBJ_NONE,
	OBJ_CONTAINER,
	OBJ_LIGHT,
	OBJ_COPY,
	OBJ_GROUP,
	OBJ_CAMERA
}							t_obj_type;

typedef struct				s_obj_light
{
	t_lgt_type				lgt_type;
	t_lgt					light;
}							t_obj_light;

typedef struct				s_obj_camera
{
	t_vec2					fov;
}							t_obj_camera;

typedef struct				s_obj_container
{
	t_shp_type				shape_type;
	t_shp					shape;
	t_mat					*material;
}							t_obj_container;

typedef struct				s_obj_group
{
	struct s_scn_object		**children;
	size_t					child_num;
}							t_obj_group;

typedef union				s_obj_content
{
	struct s_scn_object		*copy;
	t_obj_container			container;
	t_obj_group				group;
	t_obj_light				light;
	t_obj_camera			camera;
}							t_obj_content;

typedef struct				s_scn_object
{
	t_id					id;
	char					*name;
	struct s_scn_object		*parent;
	t_tfm					transform;
	t_bool					visible;
	t_obj_type				type;
	t_obj_content			content;
}							t_obj;

#endif
