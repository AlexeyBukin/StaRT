#ifndef FIO_H
#define FIO_H

#include "txr_types.h"

/*
**				fio/fio_png_read
*/

int				fio_png_read(t_txr **texture, char *filename);
int				fio_png_read_name(t_txr **texture, char *filename, char *name);

/*
**				fio/fio_read_png_buf
*/

int				png_read_buf(png_structp png_ptr, t_txr *texture);
int				png_check_type(png_structp png_ptr,
								png_infop info_ptr, t_txr *texture);

/*
**				fio/fio_png_stride
*/

int				fio_png_stride(int width);

/*
**				fio/fio_png_write
*/

int			fio_png_write(t_txr *txr, char *filename);//что тут сделать? Принять текстуру?

#endif
