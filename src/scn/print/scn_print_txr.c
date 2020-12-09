/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_print_txr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			scn_print_txr(t_scn *scn)
{
	size_t			i;
	char			*cur_type;
	static char		*txr_types[4] = {"UNKNOWN", "BW_8", "RGB_8", "RGBA_8"};

	i = 0;
	ft_printf("textures:\n");
	while (i < scn->textures_num)
	{
		if (scn->textures[i]->type == TXR_BW_8)
			cur_type = txr_types[1];
		else if (scn->textures[i]->type == TXR_RGB_8)
			cur_type = txr_types[2];
		else if (scn->textures[i]->type == TXR_RGBA_8)
			cur_type = txr_types[3];
		else
			cur_type = txr_types[0];
		ft_printf("\t%s id %d type %s filename %s\n",
			scn->textures[i]->name, scn->textures[i]->id,
			cur_type, scn->textures[i]->filename);
		i++;
	}
}
