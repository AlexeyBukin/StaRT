/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:06:14 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H


# include "srv_types.h"
# include "rt_types.h" 
# include "cmd_types.h"

//TODO add cmd_parse_add more funcs, set CMD_ADD_NUM to 5

/*
**				cmd_parse
*/

t_msg               cmd_parse_line(t_rt *rt, char *source);

/*
**				cmd_parse_command TODO replace t_rt with t_parse_help
*/

t_msg				cmd_parse_command(t_rt *rt, t_parser *parser);

/*
**				cmd/set
*/

t_msg				cmd_set(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_sphere
*/

t_msg				cmd_set_sphere(t_rt *rt, t_parser *parser);
int 				cmd_set_sphere_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_plane
*/

t_msg				cmd_set_plane(t_rt *rt, t_parser *parser);
int 				cmd_set_plane_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_material
*/

int 				cmd_set_material_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cylinder
*/

t_msg				cmd_set_cylinder(t_rt *rt, t_parser *parser);
int					cmd_set_cylinder_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cylinder
*/

t_msg				cmd_set_cone(t_rt *rt, t_parser *parser);
int					cmd_set_cone_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_group
*/

t_msg				cmd_set_group(t_rt *rt, t_parser *parser);
int					cmd_set_group_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_tools
*/

int					cmd_set_radius(t_parser *parser);

/*
**              cmd/set/cmd_set_transform_part
*/

int					cmd_read_transform_part(t_parser *parser);

/*
**              cmd/set/cmd_set_object_attributes
*/

int				cmd_set_visibility(t_parser *parser);
int				cmd_set_name(t_rt *rt, t_parser *parser);
int				cmd_set_grp(t_rt *rt, t_parser *parser);
int				cmd_set_material(t_rt *rt, t_parser *parser);

/*
**				cmd_add
*/

t_msg               cmd_add(t_rt *rt, t_parser *parser);
t_msg           	cmd_add_sphere(t_rt *rt, t_parser *parser);
t_msg				cmd_add_plane(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cone(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cylinder(t_rt *rt, t_parser *parser);
t_msg           	cmd_add_group(t_rt *rt, t_parser *parser);
t_msg				cmd_add_camera(t_rt *rt, t_parser *parser);
t_msg				cmd_add_material(t_rt *rt, t_parser *parser);

/*
**				cmd/ls
*/

t_msg				cmd_ls_scene(t_rt *rt, char *source);
t_msg				cmd_ls_sphere(t_rt *rt, char *source);

/*
**				cmd/rm
*/

// t_msg					cmd_parse_rm(t_parser *parser);

/*
**				cmd/utils/cmd_read
*/

int					cmd_read_comma(char **str);
int					cmd_read_space(char **source);
int					cmd_read_space_req(char **source);
int					cmd_read_string(char **source, char **dest);
int					cmd_read_id_name(t_scn *scn, char **source, uint *id);

/*
**				cmd/utils/cmd_read_num
*/

int					cmd_read_vec2(char **source, t_vec2 *vec);
int					cmd_read_num(char **source, t_num *num);
int					cmd_read_vec(char **source, t_vec3 *vec);
int					cmd_read_uint(char **source, uint *num);
int 				cmd_read_matrix(char **source, t_mat3x3 *mtx);

/*
**				cmd/utils/cmd_read_material
*/

int						cmd_read_material(t_parser *parser);

/*
**				cmd/utils/cmd_read_camera
*/

t_msg	   				cmd_parse_camera_flags(t_rt *rt, t_parser *parser);

#endif
