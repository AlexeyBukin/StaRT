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

int			fio_png_write_init(FILE **fp, png_structp *png, png_infop *info)
{
	if (fp == NULL || png == NULL || info == NULL)
		return (rt_err("fio_png_write_init(): given NULL pointer"));
	*fp = fopen(txr->filename, "wb");
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
}

int			fio_png_write_buf(t_txr *txr, png_structp png)
{
	size_t			y;
	png_bytep		*row_pointers;

	y = 0;
	row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * txr->height);
	if (!row_pointers)
		return (rt_err("fio_png_write_buf(): fatal: malloc error"));
	y = 0;
	while (y < txr->height)
	{
		row_pointers[y] = (png_byte*)&(txr->content[y * txr->width * 4]);
		y++;
	}
	png_write_image(png, row_pointers);
	png_write_end(png, NULL);
	free(row_pointers);
}

int			fio_png_write(t_txr *txr)//что тут сделать? Принять текстуру?
{
	FILE			*fp;
	png_structp		png;
	png_infop		info;
	size_t			y;

	if (txr == NULL)
		return (rt_err("fio_png_write(): given NULL pointer"));
	if (fio_png_write_init(&fp, &png, &info))
		return (rt_err("fio_png_write(): init fail"));
	png_set_IHDR(
			png, info, txr->width, txr->height, 8,
			PNG_COLOR_TYPE_RGBA,
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
