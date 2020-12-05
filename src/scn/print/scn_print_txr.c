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
		ft_printf("\t%s id %d type %s filename %s\n",
			scn->textures[i]->name, scn->textures[i]->id,
			scn->textures[i]->type == TXR_BW_8 ? "BW_8" :
			scn->textures[i]->type == TXR_RGB_8 ? "RGB_8":
			scn->textures[i]->type == TXR_RGBA_8 ? "RGBA_8" :
			"UNKNOWN", scn->textures[i]->filename);
		i++;
	}
}
