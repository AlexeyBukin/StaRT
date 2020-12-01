//
// Created by Hugor Chau on 11/19/20.
//

# include "rt.h"

void		scn_print_cam_params(int id, char *name, t_tfm *trf, t_vec2 fov)
{
	ft_printf("\t%s id %d fov <%.3f, %.3f> pos <%.3f, %.3f, %.3f> ", name, id,
			  fov.x, fov.y,
			  trf->pos_local.x, trf->pos_local.y, trf->pos_local.z);
	ft_printf("angle [<%.3f, %.3f, %.3f>, <%.3f, %.3f, %.3f>, <%.3f, %.3f, %.3f>]\n",
				trf->rot_local.x.x, trf->rot_local.x.y, trf->rot_local.x.z,
				trf->rot_local.y.x, trf->rot_local.y.y, trf->rot_local.y.z,
				trf->rot_local.z.x, trf->rot_local.z.y, trf->rot_local.z.z);
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
						&scn->cameras[i]->transform,
						scn->cameras[i]->fov);
		i++;
	}
}
