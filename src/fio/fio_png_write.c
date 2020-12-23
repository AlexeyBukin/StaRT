/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_lib_load.c.gpu_demo                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 23:01:55 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/24 23:01:55 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "mtl.h"
#include "gpu_types.h"
#include <stdlib.h>
#include "libft.h"
#include "png.h"
#include "rt.h"

int			fio_png_write_init(FILE **fp, png_structp *png,
								png_infop *info, char *filename)
{
	if (fp == NULL || png == NULL || info == NULL || filename == NULL)
		return (rt_err("fio_png_write_init(): given NULL pointer"));
	*fp = fopen(filename, "wb");
	if (!*fp)
		return (rt_err("fio_png_write_init(): can\'t open file"));
	*png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!*png)
	{
		fclose(*fp);
		return (rt_err("fio_png_write_init(): png_create_write_struct error"));
	}
	*info = png_create_info_struct(*png);
	if (!*info)
	{
		png_destroy_write_struct(png, NULL);
		fclose(*fp);
		return (rt_err("fio_png_write_init(): png_create_info_struct() error"));
	}
	if (setjmp(png_jmpbuf(*png)))
	{
		png_destroy_write_struct(png, info);
		fclose(*fp);
		return (rt_err("fio_png_write(): setjmp() error"));
	}
	png_init_io(*png, *fp);
	return (0);
}

int			fio_png_write_buf(t_txr *txr, png_structp png)
{
	size_t			y;
	png_bytep		*row_pointers;

	y = 0;
	row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * txr->height);
	if (!row_pointers)
		return (rt_err("fio_png_write_buf(): fatal: malloc error"));
	while (y < txr->height)
	{
		row_pointers[y] = (png_byte*)&(txr->content[y * txr->stride]);
		y++;
	}
	png_write_image(png, row_pointers);
	png_write_end(png, NULL);
	free(row_pointers);
	return (0);
}

static int			get_type(t_txr *txr, int *type)
{
	if (txr->type == TXR_RGBA_8)
		*type = PNG_COLOR_TYPE_RGBA;
	else if (txr->type == TXR_RGB_8)
		*type = PNG_COLOR_TYPE_RGB;
	else if (txr->type == TXR_BW_8)
		*type = PNG_COLOR_TYPE_GRAY;
	else
		return (rt_err("get_type(): unknown texture type"));
	return (0);
}

int			fio_png_write(t_txr *txr, char *filename)
{
	FILE			*fp;
	png_structp		png;
	png_infop		info;
	int				type;

	if (txr == NULL || filename == NULL)
		return (rt_err("fio_png_write(): given NULL pointer"));
	if (fio_png_write_init(&fp, &png, &info, filename))
		return (rt_err("fio_png_write(): init fail"));
	if (get_type(txr, &type))
		return (rt_err("fio_png_write(): unknown texture type"));
	png_set_IHDR(png, info, txr->width, txr->height, 8, type,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png, info);
	if (fio_png_write_buf(txr, png))
	{
		png_destroy_write_struct(&png, &info);
		fclose(fp);
		return (rt_err("fio_png_write(): fio_png_write_buf error"));
	}
	fclose(fp);
	png_destroy_write_struct(&png, &info);
	return (0);
}
