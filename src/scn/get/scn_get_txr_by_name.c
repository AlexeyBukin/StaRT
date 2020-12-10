/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_txr_by_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_txr				*scn_get_txr_by_name(t_scn *scn, char *name)
{
	size_t		i;

	i = 0;
	if (!scn || !name)
		return (null(rt_err("scn_get_txr_by_id(): given pointer is NULL")));
	while (i < scn->textures_num)
	{
		if (ft_strequ(scn->textures[i]->name, name))
		{
			return (scn->textures[i]);
		}
		i++;
	}
	return (NULL);
}
