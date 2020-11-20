//
// Created by Hugor Chau on 11/19/20.
//
# include "rt.h"

void			scn_print_txr(t_scn *scn)
{
	size_t		i;

	i = 0;
	ft_printf("textures:\n");
	while (i < scn->textures_num)
	{
		ft_printf("\t%s id %d\n",
			scn->textures[i]->name, scn->textures[i]->id);
		i++;
	}
}
