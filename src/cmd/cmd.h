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

#define KW_PARAM_LEN 2
#define KW_PARAM_CAP "-c"
#define KW_PARAM_POS "-p"
#define KW_PARAM_RAD "-r"
#define KW_PARAM_NORM "-n"
#define KW_PARAM_DIST "-d"

#define KW_PARAM_NAME "-N"
#define KW_PARAM_MAT "-M"

# include "srv_types.h"
# include "rt_types.h" 
# include "cmd_types.h"

# define KW_SCENE "scene"

//TODO add cmd_parse_add more funcs, set CMD_ADD_NUM to 5
# define KW_OBJECT_NUM 4
# define KW_SPHERE "sphere"
# define KW_PLANE "plane"
# define KW_CYLINDER "cylinder"
# define KW_CONE "cone"

# define KW_MATERIAL "material"

// t_msg					cmd_parse_add(t_rt *rt, char *source);

// #define CMD_LS_NUM 2
// t_msg					cmd_parse_rm(t_rt *rt, char *source);
// t_msg					cmd_parse_set(t_rt *rt, char *source);
// t_msg					cmd_parse_ls(t_rt *rt, char *source);

/*
**				cmd_parse_tree
*/

/*
**              cmd_add_extra
*/

int			        cmd_read_transform_part(t_parser *parser);

/*
**				cmd_ls
*/

t_msg					cmd_ls_scene(t_rt *rt, char *source);
t_msg					cmd_ls_sphere(t_rt *rt, char *source);

#define KW_CMD_ADD "add"
#define KW_CMD_LS "ls"
#define KW_CMD_RM "rm"
#define KW_CMD_SET "set"


/*
**				cmd_parse_tree
*/

// t_msg					cmd_parse_tree(t_rt *rt, char *str, t_parse_fw *arr, int len);

/*
**				cmd_parse
*/

//t_msg				cmd_parse_type_name(char **source, t_parse_help *helper);
t_msg               cmd_parse_line(t_rt *rt, char *source);
t_msg				cmd_parse_chain(t_rt *rt, t_parser *parser);

/*
**				cmd_parse_command
*/

t_msg           cmd_parse_command(t_parser *parser);

/*
**				cmd_add
*/

t_msg                   cmd_add(t_parser *parser);
t_msg					cmd_add_sphere(t_parser *parser);
t_msg					cmd_add_plane(t_parser *parser);


/*
**				cmd_set
*/

// # define KW_CMD_SET_NUM 4

// t_msg					cmd_set(t_rt *rt, char *source);

// t_msg					cmd_set_sphere(t_scn *scn, t_obj *sphere, char **source);
// t_msg					cmd_set_plane(t_scn *scn, t_obj *plane, char **source);
// t_msg					cmd_set_cylinder(t_scn *scn, t_obj *cylinder, char **source);
// t_msg					cmd_set_cone(t_scn *scn, t_obj *cone, char **source);

// t_msg		        	cmd_set_object_param(t_scn *scn, t_obj *obj, char **source);

/*
**				cmd_read
*/

int						cmd_read_comma(char **str);
int						cmd_read_space(char **source);
int						cmd_read_space_req(char **source);
int						cmd_read_string(char **source, char **dest);
int						cmd_read_id_name(t_scn *scn, char **source, uint *id);

/*
**				cmd_read_num
*/

int						cmd_read_num(char **source, t_num *num);
int						cmd_read_vec(char **source, t_vec3 *vec);
int						cmd_read_uint(char **source, uint *num);

#endif
