/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_SCN_ADD_H
# define START_SCN_ADD_H

# include "scn_types.h"

/*
**			scn/add/
*/

/*
**			scn_add_xxx
*/

int				scn_add_mat(t_scn *scn, t_mat *mat);
int				scn_add_txr(t_scn *scn, t_txr *txr);
int				scn_add_cam(t_scn *scn, t_cam *cam);
int				scn_add_obj(t_scn *scn, t_obj *obj);

/*
**			scn_add_to_group_xxx
*/

int				scn_add_to_group(t_scn *scn, t_obj *dest, t_obj *obj);
int				scn_add_to_group_copy(t_scn *scn, t_obj *dest, t_obj *copy);
int				scn_add_to_group_obj(t_scn *scn, t_obj *dest, t_obj *obj);
int				scn_add_to_group_grp(t_scn *scn, t_obj *dest, t_obj *grp);
int				scn_add_to_group_lgt(t_scn *scn, t_obj *dest, t_obj *lgt);
int				scn_add_to_group_cam(t_scn *scn, t_obj *dest, t_obj *cam);

#endif
