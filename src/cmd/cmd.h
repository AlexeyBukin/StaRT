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
# include "cmd_add.h"
# include "cmd_set.h"
//TODO add cmd_parse_add more funcs, set CMD_ADD_NUM to 5

/*
**				cmd_render
*/

t_msg					cmd_render(t_rt *rt, t_parser *parser);

/*
**				cmd_parse
*/

t_msg               cmd_parse_line(t_rt *rt, char *source);

/*
**				cmd_parse_command TODO replace t_rt with t_parse_help
*/

t_msg				cmd_parse_command(t_rt *rt, t_parser *parser);

/*
**				cmd/ls
*/

t_msg				cmd_ls(t_rt *rt, t_parser *parser);
t_msg				cmd_ls_scene(t_rt *rt, char *source);
t_msg				cmd_ls_sphere(t_rt *rt, char *source);

/*
**				cmd/rm
*/

t_msg				cmd_rm(t_rt *rt, t_parser *parser);
t_msg				cmd_rm_by_name(t_rt *rt, t_parser *parser, int rm_force);
int					cmd_rm_material(t_rt *rt, t_parser *parser);
t_msg				cmd_rm_error(t_parser *parser, char *message);

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
**				cmd/utils/cmd_add_obj_to_scn
*/

t_msg					cmd_add_obj_to_scn(t_rt *rt, t_parser *parser);

/*
**				cmd/utils/cmd_set_obj
*/

t_msg					cmd_set_obj_to_scn(t_rt *rt, t_parser *parser, t_obj *dest);

#endif
