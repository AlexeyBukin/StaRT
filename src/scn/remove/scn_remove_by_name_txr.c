/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_remove_by_name_txr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	copy_textures(t_scn *scn, t_txr **dst, t_txr *skip)
{
	size_t		i;

	i = 0;
	while (i < scn->textures_num)
	{
		if (scn->textures[i] == skip)
		{
			i++;
			continue ;
		}
		*dst = scn->textures[i];
		i++;
		dst++;
	}
}

int		txr_del(t_scn *scn, t_txr *txr)
{
	t_txr		**textures;

	if (!(textures =
		(t_txr **)ft_memalloc(sizeof(t_txr *) * (scn->textures_num - 1))))
		return (rt_err("txr_remove_by_name(): malloc crashed"));
	copy_textures(scn, textures, txr);
	txr_deinit(txr);
	ft_free(scn->textures);
	scn->textures = textures;
	scn->textures_num--;
	return (0);
}

int		scn_remove_by_name_txr(t_scn *scn, char *name)
{
	t_txr		*txr_to_del;

	if (!scn || !name)
		return (rt_err("txr_remove_by_name(): was given a NULL pointer"));
	txr_to_del = scn_get_txr_by_name(scn, name);
	if (!txr_to_del)
		return (rt_err("txr_remove_by_name(): there is no"
		" txr with given name"));
	return (txr_del(scn, txr_to_del));
}
