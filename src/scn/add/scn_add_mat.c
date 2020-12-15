/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_add_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scn_add_mat(t_scn *scn, t_mat *mat)
{
	t_mat		**new_array;

	if (!scn || !mat)
		return (rt_err("mat_add: given a NULL pointer"));
	if (scn_name_check(scn, mat->name))
	{
		return (rt_err("mat_add(): name collision"));
	}
	if (!(new_array = (t_mat **)ft_realloc(scn->materials,
					sizeof(t_mat *) * scn->materials_num,
					sizeof(t_mat *) * (scn->materials_num + 1))))
		return (rt_err("mat_add(): malloc returned NULL pointer"));
	scn->materials = new_array;
	scn->materials_num++;
	scn->materials[scn->materials_num - 1] = mat;
	return (0);
}
