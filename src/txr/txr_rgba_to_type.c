/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_rgba_to_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png.h"
#include "rt.h"

int				txr_rgba_to_rgb(t_txr *texture)
{
	size_t		i;
	int			old_pix_size;
	int			new_pix_size;
	char		*array;
	char		*old_array;

	if (texture == NULL)
		return (rt_err("rgba_to_rgb(): given NULL pointer"));
	if (texture->type != TXR_RGBA_8)
		return (rt_err("rgba_to_rgb(): given texture is not TXR_RGBA_8"));
	new_pix_size = 3;
	old_pix_size = 4;
	i = 0;
	array = texture->content;
	old_array = texture->content;
	while (i * old_pix_size < texture->height * texture->stride)
	{
		*((int *)array) = *((int *)old_array);
		array += new_pix_size;
		old_array += old_pix_size;
		i++;
	}
	texture->stride = texture->width * new_pix_size;
	texture->type = TXR_RGB_8;
	return (0);
}

int				txr_rgba_to_bw(t_txr *texture)
{
	txr_rgba_to_rgb(texture);
	txr_rgb_to_bw(texture);
	return (0);
}
