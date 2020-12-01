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
//	t_vec3			rot_euler_xyz;
//TODO added group in parser
	t_obj			*group;
	t_cam			*camera;
	t_mat			*material;
	t_txr			*texture;
	char			*name;
	char			*source;
	char			*cur;
}					t_parser;

#endif
