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
**				cmd_parse_command
*/

t_msg				cmd_parse_command(t_parser *parser);

/*
**				cmd/set
*/

int					cmd_set(t_parser *parser);

/*
**				cmd/set/cmd_set_sphere
*/

t_msg				cmd_set_sphere(t_parser *parser);
void				cmd_set_sphere_default(t_parser *parser);

/*
**				cmd/set/cmd_set_plane
*/

t_msg				cmd_set_plane(t_parser *parser);
void				cmd_set_plane_default(t_parser *parser);

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

int					cmd_set_obj_attributes(t_parser *parser);

/*
**				cmd_add
*/

t_msg               cmd_add(t_parser *parser);
t_msg				cmd_add_sphere(t_parser *parser);
t_msg				cmd_add_plane(t_parser *parser);

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

int					cmd_read_num(char **source, t_num *num);
int					cmd_read_vec(char **source, t_vec3 *vec);
int					cmd_read_uint(char **source, uint *num);
int 				cmd_read_matrix(char **source, t_mat3x3 *mtx);

#endif
