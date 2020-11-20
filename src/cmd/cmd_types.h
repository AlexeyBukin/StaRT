/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 19:35:41 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TYPES_H
# define CMD_TYPES_H

# include "srv_types.h"
# include "rt_types.h"

typedef struct		s_parser
{
	t_obj			*object;
	t_obj_container *container;
	t_tfm			*transform;
	t_vec3			rot_euler_xyz;
	t_cam			*camera;
	t_mat			*material;
	t_txr			*texture;
	char			*name;
	char			*source;
	char			*cur;
}					t_parser;


// typedef struct		s_parse_fw
// {
// 	t_msg			(*func)(t_rt *, char *);
// 	char			*word;
// }					t_parse_fw;

// typedef struct		s_set_fork
// {
// 	t_msg			(*func)(t_scn *, t_obj *, char **);
// 	char			*word;
// }					t_set_fork;

//union				u_comp_type
//{
//	enum e_obj_type		obj;
//	enum e_mat_type		mat;
//	enum e_cam_type		cam;
//}					t_comp_type;

//typedef struct				s_parse_help
//{
//	char					*name;
//	enum e_comp_type		type;
//	union u_comp_subtype	subtype;
//	t_component				component;
//}							t_parse_help;

// typedef struct		s_set_fork
// {
// 	t_msg			(t_scn *, t_obj *, char **);
// 	char			*word;
// }					t_set_fork;

#endif
