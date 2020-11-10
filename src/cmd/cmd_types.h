/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:59:37 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:52:53 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TYPES_H
# define CMD_TYPES_H

# include "srv_types.h"
# include "rt_types.h"

typedef struct		s_parse_fw
{
	t_msg			(*func)(t_rt *, char *);
	char			*word;
}					t_parse_fw;

#endif
