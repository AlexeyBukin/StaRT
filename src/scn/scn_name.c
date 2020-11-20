//
// Created by Hugor Chau on 11/16/20.
//

#include "rt.h"

static int		check_name_symbols(char *name)
{
	if (!*name)
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
	if (check_name_symbols(name))
		return (-1);
	if (scn_get_obj_by_name(scn, name) || scn_get_txr_by_name(scn, name))
		return (rt_err("scn_name_check(): i've sow that name!"));
	if (scn_get_cam_by_name(scn, name) || scn_get_mat_by_name(scn, name))
		return (rt_err("scn_name_check(): i've sow that name!"));
	return (0);
}
