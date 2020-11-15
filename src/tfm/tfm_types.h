/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfm_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TFM_TYPES_H
# define TFM_TYPES_H

# include "libnum.h"

typedef struct				s_scn_transform
{
	struct s_scn_transform	*parent;
	t_vec3					pos_local;
	t_vec3					pos_global;
	t_mat3x3				rot_local;
	t_mat3x3				rot_global;
}							t_tfm;

#endif
