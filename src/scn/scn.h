/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:17:36 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/03 23:17:36 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_H
# define SCN_H

# include "scn_types.h"

/*
**		scn_init
*/

int		scn_init(t_rt *rt);

/*
**		scn_id
*/

uint	scn_id();

/*
**		scn_check_arguments
*/

int		scn_check_arguments(t_scn *scn, uint mid);
t_obj	*scn_obj_by_id(t_scn *scn, uint id);
int		scn_check_mid(t_scn *scn, uint mid);
int		set_obj_mid(t_scn *scn, uint obj_id, uint mid);

/*
**		scn_add_sphere
*/

int		scn_add_sphere(t_scn *scn, t_vec3 pos, float r, uint mid);

/*
**		scn_set_sphere
*/

int		scn_set_sphere_radius(t_scn *scn, uint sphere_id, float r);


#endif
