/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:18:22 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SET_H
# define CMD_SET_H

# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"

/*
**				cmd/set
*/

t_msg			cmd_set(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_sphere
*/

t_msg			cmd_set_sphere(t_rt *rt, t_parser *parser, t_obj *dest);
int				cmd_set_sphere_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_plane
*/

t_msg			cmd_set_plane(t_rt *rt, t_parser *parser, t_obj *dest);
int				cmd_set_plane_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_material
*/

int				cmd_set_material_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cylinder
*/

t_msg			cmd_set_cylinder(t_rt *rt, t_parser *parser, t_obj *dest);
int				cmd_set_cylinder_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cone
*/

t_msg			cmd_set_cone(t_rt *rt, t_parser *parser, t_obj *dest);
int				cmd_set_cone_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_group
*/

t_msg			cmd_set_group(t_rt *rt, t_parser *parser, t_obj *dest);
int				cmd_set_group_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_material
*/

t_msg			cmd_set_material(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_camera
*/

t_msg			cmd_set_camera(t_rt *rt, t_parser *parser, t_obj *dest);

/*
**				cmd/set/cmd_set_tools
*/

int				cmd_set_radius(t_parser *parser);

/*
**              cmd/set/cmd_set_transform_part
*/

int				cmd_read_transform_part(t_parser *parser);

/*
**              cmd/set/cmd_set_object_attributes
*/

int				cmd_set_obj_visibility(t_parser *parser);
int				cmd_set_obj_name(t_rt *rt, t_parser *parser);
int				cmd_set_obj_grp(t_rt *rt, t_parser *parser);
int				cmd_set_obj_mat(t_rt *rt, t_parser *parser);

/*
**              cmd/set/cmd_set_txr
*/

t_msg			cmd_set_txr(t_rt *rt, t_parser *parser);

/*
**				cmd/utils/cmd_set_obj TODO move to set
*/

int				cmd_set_prepare_obj(t_parser *parser, t_obj *src);
t_msg			cmd_set_type(t_rt *rt, t_parser *parser);
t_msg			cmd_set_error(t_parser *parser, char *message);
t_msg			cmd_set_object(t_rt *rt, t_parser *parser);
t_msg			cmd_set_mat_to_scn(t_parser *parser, t_mat *dest);
t_msg			cmd_set_light(t_rt *rt, t_parser *parser, t_obj *dest);
t_msg			cmd_set_copy(t_rt *rt, t_parser *parser, t_obj *obj);
int				cmd_read_txr_type(t_parser *parser);
int				cmd_read_txr_filename(t_parser *parser);
t_msg			cmd_set_txr_to_scn(t_parser *parser, t_txr *dest);

#endif
