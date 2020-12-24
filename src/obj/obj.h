/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "obj_types.h"

/*
** obj_init.c
*/

int				obj_init(t_obj **dest, char *name, t_obj_type type);
int				obj_deinit(t_obj *obj);

/*
** obj_grp_init.c
*/

int				obj_grp_init(t_obj **dest, char *name);
int				obj_grp_deinit(t_obj *group);

/*
** obj_container_init.c
*/

int				obj_container_init(t_obj **dest, char *name);
int				obj_container_deinit(t_obj *cont);

/*
** obj_copy_init.c
*/

int				obj_copy_init(t_obj **dest, char *name);
int				obj_copy_deinit(t_obj *copy);

#endif
