/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/03 23:18:37 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "srv_types.h"
# include "rt_types.h"

# define MAX_PARAMS		8

typedef struct		s_word
{
	char			*w_ptr;
	int				l;
}					t_word;

/*
**				cmd_add
*/

int				cmd_add(t_rt *rt, t_word *w);

/*
**				cmd_valid
*/

int 			validate_all_components(t_rt *rt, t_word *cmd_l);
int				check_word(t_word w, t_word *check, int how_many_args);

/*
**				cmd_parse
*/

t_msg			cmd_parse(t_rt *rt, const char* request);

#endif
