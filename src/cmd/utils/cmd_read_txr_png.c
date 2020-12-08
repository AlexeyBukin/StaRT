//
// Created by Hugor Chau on 12/5/20.
//

#include "png.h"
#include "rt.h"

static int		is_png(FILE **fp, t_parser *parser)
{
	png_byte	header[8];
	int			is_png;

	*fp = fopen(parser->texture->filename, "rb");
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

static int		prepare_pnglib_structs(png_structp *png_ptr, png_infop *info_ptr, png_infop *end_info)
{
	*png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!*png_ptr)
		return (rt_err("not png"));
	png_set_user_limits(*png_ptr, 4000, 4000);
	*info_ptr = png_create_info_struct(*png_ptr);
	*end_info = png_create_info_struct(*png_ptr);
	if (!*info_ptr || !*end_info)
	{
		png_destroy_read_struct(png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		return (rt_err("no end_info"));
	}
	if (setjmp(png_jmpbuf(*png_ptr)))
	{
		png_destroy_read_struct(png_ptr, info_ptr, end_info);
		return (rt_err("setjmp() error"));
	}
	return (0);
}

static int		png_read_buf(png_structp png_ptr, png_infop info_ptr, png_infop end_info, t_parser *parser)
{
	png_bytepp		row_pointers;
	png_byte		*image_data;

	image_data = (png_bytep) malloc(parser->texture->stride * parser->texture->height * sizeof(png_byte));
	if (!image_data)
	{
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		return (rt_err("malloc error"));
	}
	row_pointers = (png_bytepp) malloc( parser->texture->height * sizeof(png_bytep) );
	if ( !row_pointers )
	{
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		free(image_data);
		return (rt_err("malloc error"));
	}
	for (unsigned int i = 0; i < parser->texture->height; ++i )
	{
		row_pointers[i] = image_data + i * parser->texture->stride;
	}
	png_read_image(png_ptr, row_pointers);
	if (parser->texture->content)
		ft_memdel((void **)&parser->texture->content);
	parser->texture->content = (char *)image_data;
	ft_free(row_pointers);
	return (0);
}

static int		check_type(png_structp png_ptr, png_infop info_ptr, t_parser *parser)
{
	int				color_type;

	png_get_IHDR(png_ptr, info_ptr, NULL, NULL, NULL, &color_type, NULL, NULL, NULL);
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

static int		png_get_size(png_structp png_ptr, png_infop info_ptr, t_parser *parser)
{
	png_uint_32		t_width;
	png_uint_32		t_height;
	int				bit_depth;
	int				color_type;

	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	(png_get_IHDR(png_ptr, info_ptr,
				&t_width, &t_height,
				&bit_depth, &color_type, NULL, NULL, NULL));
//		return (-1);
	parser->texture->width = t_width;
	parser->texture->height = t_height;
	png_read_update_info(png_ptr, info_ptr);
	parser->texture->stride = png_get_rowbytes(png_ptr, info_ptr);
	return (0);
}

int		cmd_read_png(t_parser *parser)
{
	FILE			*fp;
	png_structp		png_ptr;
	png_infop		info_ptr;
	png_infop		end_info;

	if (is_png(&fp, parser))
		return (rt_err("cmd_read_png(): given file is not png"));
	if (prepare_pnglib_structs(&png_ptr, &info_ptr, &end_info))
	{
		fclose(fp);
		return (rt_err("cmd_read_png(): can\'t prepare png structs"));
	}
	png_init_io(png_ptr, fp);
	if (png_get_size(png_ptr, info_ptr, parser))
	{
		fclose(fp);
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		return (rt_err("png size error"));
	}
	if (check_type(png_ptr, info_ptr, parser))
	{
		fclose(fp);
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		return (rt_err("check_type(): type error"));
	}
	if (png_read_buf(png_ptr, info_ptr, end_info, parser))
	{
		fclose(fp);
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		return (rt_err("check_type(): png_read_buf error"));
	}
	fclose(fp);
	png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
	return (0);
}
