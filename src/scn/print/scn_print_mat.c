//
// Created by Hugor Chau on 11/19/20.
//

# include "rt.h"

void			scn_print_mat(t_scn *scn)
{
	size_t		i;

	i = 0;
	ft_printf("materials:\n");
	while (i < scn->materials_num)
	{
		ft_printf("\t%s id %d\n",
				scn->materials[i]->name, scn->materials[i]->id);
		i++;
	}
}
