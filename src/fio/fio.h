/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fio.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:05:10 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 01:06:28 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIO_H
# define FIO_H

# include "txr_types.h"

/*
**				fio/fio_png_read
*/

int				fio_png_read(t_txr **texture, char *filename);
int				fio_png_read_name(t_txr **texture, char *filename, char *name);

/*
**				fio/fio_png_read_buf
*/

int				png_read_buf(png_structp png_ptr, t_txr *texture);
int				png_check_type(png_structp png_ptr,
								png_infop info_ptr, t_txr *texture);

/*
**				fio/fio_png_reader
*/

int				png_read(t_txr *tmp);

/*
**				fio/fio_png_stride
*/

int				fio_png_stride(int width);

/*
**				fio/fio_png_write
*/

int				fio_png_write(t_txr *txr, char *filename);

#endif
