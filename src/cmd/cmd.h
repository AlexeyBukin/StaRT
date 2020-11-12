/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/11 11:42:37 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"

/*
**				cmd_add
*/

# define CMD_ADD_NUM 1
# define KW_SPHERE "sphere"
# define KW_SCENE "scene"

t_msg					cmd_parse_add(t_rt *rt, char *source);

#define CMD_LS_NUM 2
t_msg					cmd_parse_rm(t_rt *rt, char *source);
t_msg					cmd_parse_set(t_rt *rt, char *source);
t_msg					cmd_parse_ls(t_rt *rt, char *source);

/*
**				cmd_ls
*/

t_msg					cmd_ls_scene(t_rt *rt, char *source);
t_msg					cmd_ls_sphere(t_rt *rt, char *source);

/*
**				cmd_parse
*/

#define CMD_MAIN_NUM 4
#define KW_ADD "add"
#define KW_LS "ls"
#define KW_RM "rm"
#define KW_SET "set"


t_msg					cmd_parse_line(t_rt *rt, char *source);

/*
**				cmd_parse_tree
*/

t_msg					cmd_parse_tree(t_rt *rt, char *str, t_parse_fw *arr, int len);

/*
**				cmd_add
*/

t_msg					cmd_add_sphere(t_rt *rt, char *source);
t_msg					cmd_add_plane(t_rt *rt, char *source);

/*
**				cmd_set_sphere
*/

t_msg					cmd_set_sphere_pos(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_radius(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_material(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_name(char **source, t_sphere *sphere);

/*
**				cmd_set_plane
*/

t_msg					cmd_set_plane_norm(char **source, t_plane *plane);
t_msg					cmd_set_plane_dist(char **source, t_plane *plane);
t_msg					cmd_set_plane_material(char **source, t_plane *plane);
t_msg					cmd_set_plane_name(char **source, t_plane *plane);

/*
**				cmd_read
*/

int						cmd_read_comma(char **str);
int						cmd_read_space(char **source);
int						cmd_read_space_req(char **source);
int						cmd_read_string(char **source, char **dest);
int						cmd_read_id_name(t_rt *rt, char **source, uint *id);

int						cmd_read_num(char **source, t_num *num);
int						cmd_read_vec(char **source, t_vec3 *vec);
int						cmd_read_uint(char **source, uint *num);

#endif
