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

# include "scn_types.h"

int		scn_init(t_rt *rt);
uint	scn_id();
int		check_arguments(t_scn *scn, uint mid);
int		scn_add_sphere(t_scn *scn, t_vec3 pos, float r, uint mid);
int		scn_add_plane(t_scn *scn, t_vec3 n, float d, uint mid);
int		scn_add_cone(t_scn *scn, t_vec3 pos, float r, t_vec3 cap, uint mid);
int		scn_add_cylinder(t_scn *scn, t_vec3 pos, t_vec3 cap, float r, uint mid);

#endif
