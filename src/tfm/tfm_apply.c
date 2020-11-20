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
	tfm->pos_local = vec3_zero();
	tfm->rot_global = mat3x3_identity();
	tfm->rot_local = mat3x3_identity();
	return (0);
}
