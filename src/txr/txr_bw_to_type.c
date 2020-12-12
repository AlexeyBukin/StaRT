/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_obj_to_scn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png.h"
#include "rt.h"

static void		bw_to_rgb_cycle(char *array, t_txr *texture,
								int old_pix_size, int new_pix_size)
{
	size_t		i;
	char		*old_array;

	i = 0;
	old_array = texture->content;
	while (i * old_pix_size < texture->height * texture->stride)
	{
		array[0] = (old_array[0] + old_array[1]) % 256;
		array[1] = array[0];
		array[2] = array[0];
		array += new_pix_size;
		old_array += old_pix_size;
		i++;
	}
}

int				txr_bw_to_rgb(t_txr *texture)
{
//	size_t		i;
	int			old_pix_size;
	int			new_pix_size;
	char		*array;
//	char		*old_array;

	if (texture == NULL)
		return (rt_err("rgba_to_rgb(): given NULL pointer"));
	if (texture->type != TXR_BW_8)
		return (rt_err("rgba_to_rgb(): given texture is not TXR_RGBA_8"));
	new_pix_size = 3;
	old_pix_size = 2;
//	i = 0;
	array = ft_memalloc(texture->height * texture->width * new_pix_size);
//	old_array = texture->content;
//	while (i * old_pix_size < texture->height * texture->stride)
//	{
//		array[new_pix_size * i + 0] = (old_array[0] + old_array[1]) % 256;
//		array[new_pix_size * i + 1] = array[new_pix_size * i + 0];
//		array[new_pix_size * i + 2] = array[new_pix_size * i + 0];
//		old_array += old_pix_size;
//		i++;
//	}
	bw_to_rgb_cycle(array, texture, old_pix_size, new_pix_size);
	texture->stride = texture->width * new_pix_size;
	texture->type = TXR_RGB_8;
	ft_free(texture->content);
	texture->content = array;
	return (0);
}

static void		bw_to_rgba_cycle(char *array, t_txr *texture,
								int old_pix_size, int new_pix_size)
{
	size_t		i;
	char		*old_array;

	i = 0;
	old_array = texture->content;
	while (i * old_pix_size < texture->height * texture->stride)
	{
		array[0] = (old_array[0] + old_array[1]) % 256;
		array[1] = array[0];
		array[2] = array[0];
		array[3] = 0;
		array += new_pix_size;
		old_array += old_pix_size;
		i++;
	}
}

int				txr_bw_to_rgba(t_txr *texture)
{
//	size_t		i;
	int			old_pix_size;
	int			new_pix_size;
	char		*array;
//	char		*a;
//	char		*old_array;

	if (texture == NULL)
		return (rt_err("rgba_to_rgb(): given NULL pointer"));
	if (texture->type != TXR_BW_8)
		return (rt_err("rgba_to_rgb(): given texture is not TXR_RGBA_8"));
	new_pix_size = 4;
	old_pix_size = 2;
//	i = 0;
	array = ft_memalloc(texture->height * texture->width * new_pix_size);
//	a = array;
//	old_array = texture->content;
//	while (i * old_pix_size < texture->height * texture->stride)
//	{
//		array[new_pix_size * i + 0] = (old_array[0] + old_array[1]) % 256;
//		array[new_pix_size * i + 1] = array[new_pix_size * i + 0];
//		array[new_pix_size * i + 2] = array[new_pix_size * i + 0];
//		array[new_pix_size * i + 3] = 0;
//		old_array += old_pix_size;
//		i++;
//	}
	bw_to_rgba_cycle(array, texture, old_pix_size, new_pix_size);
	texture->stride = texture->width * new_pix_size;
	texture->type = TXR_RGBA_8;
	ft_free(texture->content);
	texture->content = array;
	return (0);
}
