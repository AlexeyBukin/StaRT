/*
**		i'm sorry it's tmp from fio directory, afraid to merge
*/

#include "png.h"
#include "txr_types.h"
#include "err.h"
#include "libft.h"

int				png_check_type_tmp(png_structp png_ptr,
								  png_infop info_ptr, t_txr *texture)
{
	int				color_type;

	png_get_IHDR(png_ptr, info_ptr, NULL, NULL,
				 NULL, &color_type, NULL, NULL, NULL);
	if (color_type == PNG_COLOR_TYPE_RGBA)
	{
		texture->type = TXR_RGBA_8;
//		if (texture->type != TXR_RGBA_8)
//			return (rt_err("expected another color type"));
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_RGB)
	{
		texture->type = TXR_RGB_8;
//		if (texture->type != TXR_RGB_8)
//			return (rt_err("expected another color type"));
		return (0);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		texture->type = TXR_BW_8;
//		if (texture->type != TXR_BW_8)
//			return (rt_err("expected another color type"));
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
	texture->content = (unsigned char *)image_data;
	ft_free(row_pointers);
	return (0);
}

int				png_read_buf_tmp(png_structp png_ptr, t_txr *texture)
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
	return (0);
}

int				fio_read_png_tmp(t_txr *texture)
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
	if (png_check_type_tmp(png_ptr, info_ptr, texture))
		return (png_read_error(png_ptr, info_ptr, end_info, fp));
	if (png_read_buf_tmp(png_ptr, texture))
		return (png_read_error(png_ptr, info_ptr, end_info, fp));
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	return (0);
}