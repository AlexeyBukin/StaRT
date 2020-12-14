/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfm_apply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:10:48 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			tfm_apply_from_to(t_tfm *from, t_tfm *to)
{
	// t_qtn	q_rotf;
	// t_qtn	q_rott;
	
	if (from == NULL || to == NULL)
		return (rt_err("Given pointer is NULL"));
	// to->pos_global = vec3_plus(from->pos_global, to->pos_local);
	// q_rotf = matrix_to_qtn(from->rot_global);
	// q_rott = matrix_to_qtn(to->rot_local);
	// to->rot_global = qtn_to_matrix(qtn_mult_qtn(q_rotf, q_rott));
	// to->rot_global = to->rot_local;
	return (0);
}
