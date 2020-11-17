//
// Created by Hugor Chau on 11/17/20.
//

#include "rt.h"

int		txr_add(t_scn *scn, t_txr *txr)
{
	t_txr		**new_array;
	t_txr		*txr_copy;

	if ((txr_copy = scn_get_txr_by_name(scn, txr->name)))
	{
		if (txr_copy == txr)
			return (rt_err("mat_add(): object is inside the scene already"));
		txr_deinit(txr);
		return (rt_err("txr_add(): name collision"));
	}
	if (!(new_array = (t_txr **)ft_realloc(scn->textures, sizeof(t_txr *) * scn->textures_num,
			sizeof(t_txr *) * (scn->textures_num + 1))))
	{
		txr_deinit(txr);
		return (rt_err("txr_add(): malloc returned NULL pointer"));
	}
	scn->textures = new_array;
	scn->textures_num++;
	scn->textures[scn->textures_num - 1] = txr;
	return (0);
}
