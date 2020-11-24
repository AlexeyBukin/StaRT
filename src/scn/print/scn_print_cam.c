//
// Created by Hugor Chau on 11/19/20.
//

# include "rt.h"

void		scn_print_cam_params(int id, char *name, t_tfm *trf)
{
	ft_printf("\t%s id %d pos <%d, %d, %d>\n", name, id,
			  trf->pos_local.x, trf->pos_local.y, trf->pos_local.z);
}

void			scn_print_cam(t_scn *scn)
{
	size_t		i;

	i = 0;
	ft_printf("cameras:\n");
	while (i < scn->cameras_num)
	{
		scn_print_cam_params(scn->cameras[i]->id,
						scn->cameras[i]->name,
						&scn->cameras[i]->transform);
		i++;
	}
}
