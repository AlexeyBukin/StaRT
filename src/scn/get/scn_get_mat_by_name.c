/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_get_mat_by_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat				*scn_get_mat_by_name(t_scn *scn, char *name)
{
	size_t		i;

	i = 0;
	if (!scn || !name)
		return (null(rt_err("scn_get_txr_by_id(): given pointer is NULL")));
	while (i < scn->materials_num)
	{
		if (ft_strequ(scn->materials[i]->name, name))
			return (scn->materials[i]);
		i++;
	}
	return (NULL);
}
