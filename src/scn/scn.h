/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:17:36 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_H
# define SCN_H

# define ALLOC_SIZE_STEP	16
# include "scn_types.h"
# include "obj_types.h"
# include "scn_add.h"
# define GET_OBJ "object"
# define GET_MATERIAL "material"

/*
**		scn_init
*/

int					scn_init(t_scn **dest);
int					scn_deinit(t_scn *dest);

/*
**		scn_id
*/

uint				scn_id();

/*
**		scn/get/
*/

t_obj				*scn_get_obj_by_name(t_scn *scn, char *name);
t_obj				*scn_get_obj_by_id(t_scn *scn, t_id id);
t_txr				*scn_get_txr_by_name(t_scn *scn, char *name);
t_cam				*scn_get_cam_by_name(t_scn *scn, char *name);
t_mat				*scn_get_mat_by_name(t_scn *scn, char *name);

/*
**		scn_check_arguments
**		TODO: delete?
*/

t_obj				*scn_obj_by_id(t_scn *scn, uint id);
int					scn_check_mid(t_scn *scn, uint mid);
int					set_obj_mid(t_scn *scn, uint obj_id, uint mid);

/*
**		scn/get
*/

int					scn_get_obj_num(t_scn *scn);
t_obj				*scn_get_obj_by_name(t_scn *scn, char *obj_name);

/*
**		scn_get_shape
*/

struct s_sphere		*scn_get_sphere(t_scn *scn, char *name);
struct s_plane		*scn_get_plane(t_scn *scn, char *name);
struct s_cone		*scn_get_cone(t_scn *scn, char *name);
struct s_cylinder	*scn_get_cylinder(t_scn *scn, char *name);

/*
**		scn_name
*/

int					scn_name_check(t_scn *scn, char *name);

//TODO implement funcs
//int				scn_component_get_id(t_scn *scn, t_component_type type, char *name, uint *id);
//int				scn_component_get_name(t_scn *scn, uint comp_id);
//int				scn_component_get_type(t_scn *scn, uint comp_id, enum e_component_type *type);

int					scn_component_set_name(t_scn *scn,
							uint comp_id, char *name);

/*
**			scn/print
*/

int					scn_print(t_scn *scn);
void				scn_print_cam(t_scn *scn);
void				scn_print_txr(t_scn *scn);
void				scn_print_mat(t_scn *scn);
int					scn_print_grps(t_scn *scn);
int					scn_print_obj(t_obj *obj, int tab_num);
void				write_tabs(int tab_num);
int					scn_print_grp_rec(t_obj *obj, int tab_num);
/*
**			scn/remove/
*/

int					scn_remove_by_name_txr(t_scn *scn, char *name);
int					scn_remove_by_name_mat(t_scn *scn, char *name);
int					scn_remove_by_name_cam(t_scn *scn, char *name);

int					scn_remove_by_name_grp(t_scn *scn, char *name);
int					scn_remove_by_name_obj(t_scn *scn, char *name);
int					scn_remove_by_name_copy(t_scn *scn, char *name);
int					scn_remove_by_name_lgt(t_scn *scn, char *name);

int					delete_copy(t_obj *obj);
int					del_obj_copies(t_obj *from, t_obj *original);
void				grp_memmove(t_obj_group *grp, t_obj **dst, t_obj *del);

/*
**			scn/utils/
*/

int					scn_group_inc(t_obj_group *grp);
int					scn_del_copies_of(t_obj *from, t_obj *original);

/*
**		scn/move
*/

int					scn_move_obj(t_scn *scn, t_obj *dst, t_obj *obj);

#endif
