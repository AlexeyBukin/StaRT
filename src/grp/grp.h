/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 21:57:47 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRP_H
# define GRP_H

# include "scn_types.h"

/*
** grp_init.c
*/

int				grp_init(t_obj **dest, char *name);
int				grp_deinit(t_obj *group);

/*
** grp_remove_by_name.c
*/

int				grp_remove_by_name(t_obj *from, char *name);

#endif
