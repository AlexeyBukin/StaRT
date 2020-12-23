/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_png_buf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png.h"
#include "rt.h"

int				png_check_type(png_structp png_ptr,
						png_infop info_ptr, t_txr *texture)
{
	int				color_type;

	png_get_IHDR(png_ptr, info_ptr, NULL, NULL,
			NULL, &color_type, NULL, NULL, NULL);
	if (color_type == PNG_COLOR_TYPE_RGBA)
	{
		texture->type = TXR_RGBA_8;
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_RGB)
	{
		texture->type = TXR_RGB_8;
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		texture->type = TXR_BW_8;
		return (0);
	}
	return (rt_err("unknown texture type"));
}

static int		txr_png_read_rows(png_structp png_ptr,
					t_txr *texture, png_byte *image_data)
{
	png_bytepp		row_pointers;
	size_t			i;

	i = 0;
	row_pointers = (png_bytepp)ft_memalloc(texture->height
					* sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		free(image_data);
		return (rt_err("malloc error"));
	}
	while (i < texture->height)
	{
		row_pointers[i] = image_data + i
						* texture->stride;
		i++;
	}
	png_read_image(png_ptr, row_pointers);
	if (texture->content)
		ft_memdel((void **)&texture->content);
	texture->content = (char *)image_data;
	ft_free(row_pointers);
	return (0);
}

int				png_read_buf(png_structp png_ptr, t_txr *texture)
{
	png_byte		*image_data;

	image_data = (png_bytep)malloc(texture->stride
			* texture->height * sizeof(png_byte));
	if (!image_data)
		return (rt_err("malloc error"));
	if (txr_png_read_rows(png_ptr, texture, image_data))
		return (rt_err("png_read_buf(): error"));
	return (0);
}
