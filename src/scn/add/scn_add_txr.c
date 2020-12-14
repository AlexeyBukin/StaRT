/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_txr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_add_txr(t_scn *scn, t_txr *txr)
{
	t_txr		**new_array;

	if (!scn || !txr)
		return (rt_err("txr_add(): was given a NULL pointer"));
	if (scn_name_check(scn, txr->name))
	{
		ft_printf("2\n");
		return (rt_err("txr_add(): name collision"));
	}
	if (!(new_array = (t_txr **)ft_realloc(scn->textures,
			sizeof(t_txr *) * scn->textures_num,
			sizeof(t_txr *) * (scn->textures_num + 1))))
		return (rt_err("txr_add(): malloc returned NULL pointer"));
	scn->textures = new_array;
	scn->textures_num++;
	scn->textures[scn->textures_num - 1] = txr;
	return (0);
}
