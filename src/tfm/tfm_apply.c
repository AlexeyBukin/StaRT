/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfm_apply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		tfm_apply_from_to(t_tfm *from, t_tfm *to)
{
	if (from == NULL || to == NULL)
		return (rt_err("Given pointer is NULL"));
	to->pos_global = vec3_plus(from->pos_global, to->pos_local);
	// TODO : global rotation of rot_origin
	// TODO : get_quant_rot
	// TODO : apply_quant_rot
	//	to->rot_global = mat3x3_identity();
	to->rot_global = to->rot_local;
	return (0);
}
