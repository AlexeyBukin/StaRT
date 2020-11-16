//
// Created by Hugor Chau on 11/16/20.
//

#include "rt.h"

static int		check_symbols(char *name)
{
	while (*name)
	{
		if ((*name < 'a' || *name > 'z') && (*name != '_')
			&& (*name < '0' || *name > '9'))
			return (rt_err("scn_name_check(): name has an incorrect symbol"));
		name++;
	}
	return (0);
}

static int		check_array(char *name, t_component_base **array, int arr_len)
{
	size_t		i;

	i = 0;
	while (i < arr_len)
	{
		if (!(ft_strcmp(name, array[i]->name)))
			return (-1);
		i++;
	}
	return (0);
}

int				scn_name_check(t_scn *scn, char *name)
{
	int		i;

	i = 0;
	if (!name)
		return (rt_err("scn_name_check(): name was given as a NULL pointer"));
	if (!scn)
		return (rt_err("scn_name_check(): scn was given as a NULL pointer"));
	if (!*name)
		return (rt_err("scn_name_check(): name is "
		"an empty string (name[0] == \'\\0\')"));
	if (check_symbols(name) == -1)
		return (-1);
	if (check_array(name, scn->materials, scn->materials_num) == -1)
		return (rt_err("scn_name_check(): name was already used in materials"));
	if (check_array(name, scn->textures, scn->textures_num) == -1)
		return (rt_err("scn_name_check(): name was already used in textures"));
	if (check_array(name, scn->cameras, scn->cameras_num) == -1)
		return (rt_err("scn_name_check(): name was already used in cameras"));
	return (0);
}
