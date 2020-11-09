/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 01:33:25 by kcharla          ###   ########.fr       */
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

int				cmd_parse_add(t_rt *rt, char *str);

/*
**				cmd_parse
*/

#define CMD_MAIN_NUM 4
#define KW_ADD "add"
#define KW_LS "ls"
#define KW_RM "rm"
#define KW_SET "set"

t_msg			cmd_parse(t_rt *rt, const char* request);

/*
**				cmd_parse_tree
*/

t_msg			cmd_parse_tree(t_rt *rt, char *str, t_parse_fw *arr, int len);

/*
**				cmd_set_sphere
*/

t_msg					cmd_set_sphere_pos(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_radius(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_material(char **source, t_sphere *sphere);
t_msg					cmd_set_sphere_name(char **source, t_sphere *sphere);

/*
**				cmd_read
*/

int						cmd_read_comma(char **str);
int						cmd_read_space(char **source);
int						cmd_read_space_req(char **source);

t_num					cmd_read_num(char **source);
int						cmd_read_vec(char **source, t_vec3 *vec);

#endif
