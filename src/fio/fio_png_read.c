/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_txr_png.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png.h"
#include "rt.h"

static int		png_read_error(png_structp png_ptr, png_infop info_ptr,
							png_infop end_info, FILE *fp)
{
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	return (-1);
}

static int		is_png(FILE **fp, t_txr *texture)
{
	png_byte	header[8];
	int			is_png;

	*fp = fopen(texture->filename, "rb");
	if (!*fp)
		return (rt_err("can\'t open file"));
	fread(header, sizeof(png_byte), 8, *fp);
	is_png = png_sig_cmp(header, 0, 8);
	if (is_png)
	{
		fclose(*fp);
		return (rt_err("not png"));
	}
	return (0);
}

static int		prepare_pnglib_structs(png_structp *png_ptr,
				png_infop *info_ptr, png_infop *end_info)
{
	*png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!*png_ptr)
		return (rt_err("not png"));
	png_set_user_limits(*png_ptr, 4000, 4000);
	*info_ptr = png_create_info_struct(*png_ptr);
	*end_info = png_create_info_struct(*png_ptr);
	if (*info_ptr == NULL)
	{
		png_destroy_read_struct(png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return (rt_err("no end_info"));
	}
	if (*end_info == NULL)
	{
		png_destroy_read_struct(png_ptr, info_ptr, (png_infopp)NULL);
		return (rt_err("no end_info"));
	}
	if (setjmp(png_jmpbuf(*png_ptr)))
	{
		png_destroy_read_struct(png_ptr, info_ptr, end_info);
		return (rt_err("setjmp() error"));
	}
	return (0);
}

static int		png_get_size(png_structp png_ptr,
						png_infop info_ptr, t_txr *texture)
{
	png_uint_32		t_width;
	png_uint_32		t_height;
	int				bit_depth;
	int				color_type;

	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr,
				&t_width, &t_height,
				&bit_depth, &color_type, NULL, NULL, NULL);
	texture->width = t_width;
	texture->height = t_height;
	png_read_update_info(png_ptr, info_ptr);
	texture->stride =
			png_get_rowbytes(png_ptr, info_ptr);
	texture->stride = fio_png_stride(texture->stride);
	return (0);
}

int				fio_read_png(t_txr *texture)
{
	FILE			*fp;
	png_structp		png_ptr;
	png_infop		info_ptr;
	png_infop		end_info;

	if (is_png(&fp, texture))
		return (rt_err("cmd_read_png(): given file is not png"));
	if (prepare_pnglib_structs(&png_ptr, &info_ptr, &end_info))
	{
		fclose(fp);
		return (rt_err("cmd_read_png(): can\'t prepare png structs"));
	}
	png_init_io(png_ptr, fp);
	if (png_get_size(png_ptr, info_ptr, texture))
		return (png_read_error(png_ptr, info_ptr, end_info, fp));
	if (png_check_type(png_ptr, info_ptr, texture))
		return (png_read_error(png_ptr, info_ptr, end_info, fp));
	if (png_read_buf(png_ptr, texture))
		return (png_read_error(png_ptr, info_ptr, end_info, fp));
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	return (0);
}
