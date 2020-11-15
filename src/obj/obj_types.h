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

typedef struct				s_obj_container
{
	t_shp_type				shape_type;
	t_shp					shape;
	t_mat					*material;
}							t_obj_container;

typedef struct				s_obj_group
{
	struct s_scn_object		*children;
	size_t					child_num;
}							t_obj_group;

typedef enum				s_obj_type
{
	OBJ_NONE,
	OBJ_CONTAINER,
	OBJ_COPY,
	OBJ_GROUP
}							t_obj_type;

typedef union				s_obj_content
{
	t_obj_container			container;
	t_obj_container			*copy;
	t_obj_group				group;
}							t_obj_content;

typedef struct				s_scn_object
{
	t_id					id;
	struct s_scn_object		*parent;
	t_tfm					transform;
	char					*name;
	t_bool					visible;
	t_obj_type				type;
	t_obj_content			content;
}							t_obj;

#endif
