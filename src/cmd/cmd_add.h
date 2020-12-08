/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ADD_H
# define CMD_ADD_H

# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"

/*
**				cmd/add
*/

t_msg				cmd_add_sphere(t_rt *rt, t_parser *parser);
t_msg				cmd_add_plane(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cone(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cylinder(t_rt *rt, t_parser *parser);
t_msg				cmd_add_group(t_rt *rt, t_parser *parser);
t_msg				cmd_add_camera(t_rt *rt, t_parser *parser);
t_msg				cmd_add_material(t_rt *rt, t_parser *parser);
t_msg				cmd_add_light(t_rt *rt, t_parser *parser);
t_msg				cmd_add_copy(t_rt *rt, t_parser *parser);
t_msg				cmd_add_txr(t_rt *rt, t_parser *parser);
int					cmd_add_txr_to_scn(t_rt *rt, t_parser *parser);

/*
**				cmd_add
*/

t_msg				cmd_add_error(t_parser *parser, char *error_message);
t_msg				cmd_add(t_rt *rt, t_parser *parser);

#endif
