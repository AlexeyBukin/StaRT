//
// Created by Hugor Chau on 11/17/20.
//

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
			ft_putstr(scn->textures[i]->name);
			return (scn->textures[i]);
		}
		i++;
	}
	return (NULL);
}
