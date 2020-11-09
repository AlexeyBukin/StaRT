/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "srv_types.h"
# include "rt_types.h"

# define MAX_PARAMS		8

typedef struct		s_parse_fw
{
	t_msg			(*func)(t_rt *, char *);
	char			*word;
}					t_parse_fw;


/*
**				cmd_add
*/

# define CMD_ADD_NUM 1
# define KW_SPHERE "sphere"

int				cmd_parse_add(t_rt *rt, char *str);

/*
**				cmd_valid
*/

int 			validate_all_components(t_rt *rt, t_word *cmd_l);
int				check_word(t_word w, t_word *check, int how_many_args);

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

#endif
