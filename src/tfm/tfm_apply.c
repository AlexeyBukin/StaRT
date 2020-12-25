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

/*
** TODO apply rotation
*/

int			tfm_apply_from_to(t_tfm *from, t_tfm *to)
{
	if (to == NULL)
		return (rt_err("Given pointer is NULL"));
	if (from != NULL)
	{
		to->pos_global = vec3_plus(from->pos_global, to->pos_local);
		to->rot_global = to->rot_local;
	}
	return (0);
}
