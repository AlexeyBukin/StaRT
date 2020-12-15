/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		scn_name_check_symbols(char *name)
{
	if (name == NULL)
		return (rt_err("Given pointer is NULL"));
	if (name[0] == '\0')
		return (rt_err("check_name_symbols(): name is "
		"an empty string"));
	while (*name)
	{
		if (!(ft_isalpha(*name) || ft_isdigit(*name) || *name == '_'))
			return (rt_err("scn_name_check(): name has an incorrect symbol"));
		name++;
	}
	return (0);
}

int				scn_name_check(t_scn *scn, char *name)
{
	if (!name)
		return (rt_err("scn_name_check(): name was given as a NULL pointer"));
	if (!scn)
		return (rt_err("scn_name_check(): scn was given as a NULL pointer"));
	if (scn_name_check_symbols(name))
		return (rt_err("scn_name_check(): name has an incorrect symbol"));
	if (scn_get_obj_by_name(scn, name) || scn_get_txr_by_name(scn, name))
		return (rt_err("scn_name_check(): not a unique name"));
	return (0);
}
