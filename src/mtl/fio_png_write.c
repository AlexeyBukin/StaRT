/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_lib_load.c.gpu_demo                                :+:      :+:    :+:   */
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

int fio_png_write(char *data, int width, int height, char *filename) {
	FILE *fp = fopen(filename, "wb");
	if(!fp) abort();

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) return (-1);

	png_infop info = png_create_info_struct(png);
	if (!info) return (-1);

	if (setjmp(png_jmpbuf(png))) abort();

	png_init_io(png, fp);

	// Output is 8bit depth, RGBA format.
	png_set_IHDR(
			png,
			info,
			width, height,
			8,
			PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
	// Use png_set_filler().
	//png_set_filler(png, 0, PNG_FILLER_AFTER);

	png_bytep *row_pointers = NULL;
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	if (!row_pointers) return (-1);
	int y;
	for(y = 0; y < height; y++)
	{
//		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
		row_pointers[y] = (png_byte*)&(data[0]);
	}

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

//	for(y = 0; y < height; y++) {
//		free(row_pointers[y]);
//	}
	free(row_pointers);

	fclose(fp);

	png_destroy_write_struct(&png, &info);
	return (0);
}
