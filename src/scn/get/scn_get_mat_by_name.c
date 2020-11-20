//
// Created by Hugor Chau on 11/17/20.
//

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
