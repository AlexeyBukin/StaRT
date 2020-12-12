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

int				check_type(png_structp png_ptr,
						png_infop info_ptr, t_parser *parser)
{
	int				color_type;

	png_get_IHDR(png_ptr, info_ptr, NULL, NULL,
			NULL, &color_type, NULL, NULL, NULL);
	if (color_type == PNG_COLOR_TYPE_RGBA)
	{
		if (parser->texture->type != TXR_RGBA_8)
			return (rt_err("expected another color type"));
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_RGB)
	{
		if (parser->texture->type != TXR_RGB_8)
			return (rt_err("expected another color type"));
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		if (parser->texture->type != TXR_BW_8)
			return (rt_err("expected another color type"));
		return (0);
	}
	return (rt_err("unknown texture type"));
}

static int		txr_png_read_rows(png_structp png_ptr,
					t_parser *parser, png_byte *image_data)
{
	png_bytepp		row_pointers;
	size_t			i;

	i = 0;
	row_pointers = (png_bytepp)ft_memalloc(parser->texture->height
					* sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		free(image_data);
		return (rt_err("malloc error"));
	}
	while (i < parser->texture->height)
	{
		row_pointers[i] = image_data + i
						* parser->texture->stride;
		i++;
	}
	png_read_image(png_ptr, row_pointers);
	if (parser->texture->content)
		ft_memdel((void **)&parser->texture->content);
	parser->texture->content = (char *)image_data;
	ft_free(row_pointers);
	return (0);
}

int				png_read_buf(png_structp png_ptr, t_parser *parser)
{
	png_byte		*image_data;

	image_data = (png_bytep)malloc(parser->texture->stride
			* parser->texture->height * sizeof(png_byte));
	if (!image_data)
		return (rt_err("malloc error"));
	if (txr_png_read_rows(png_ptr, parser, image_data))
		return (rt_err("png_read_buf(): error"));
//	if (parser->texture->type == TXR_RGBA_8)
//	{
//		if (txr_rgba_to_bw(parser->texture))
//			return (rt_err("WTF"));
//		if (txr_bw_to_rgb(parser->texture))
//			return (rt_err("WTF2"));
//	}
	return (0);
}
