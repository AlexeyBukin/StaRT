//
// Created by Hugor Chau on 11/19/20.
//

#include "rt.h"

int			scn_print(t_scn *scn)
{
	if (!scn)
		return (rt_err("scn_print(): given pointer is NULL"));
	ft_printf("scene:\n");
	scn_print_cam(scn);
	scn_print_txr(scn);
	scn_print_mat(scn);
	if (scn_print_grps(scn))
		return (-1);
	return (0);
}
