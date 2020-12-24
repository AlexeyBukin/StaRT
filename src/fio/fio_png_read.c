/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fio_png_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png.h"
#include "rt.h"

int				fio_png_read_name(t_txr **texture, char *filename, char *name)
{
	t_txr			*tmp;

	if (texture == NULL || filename == NULL || name == NULL)
		return (rt_err("fio_png_read_name(): fatal: given NULL pointer"));
	if (txr_init_default(&tmp, name))
		return (rt_err("fio_png_read_name(): fatal: malloc error"));
	tmp->filename = filename;
	if (png_read(tmp))
	{
		txr_deinit(tmp);
		return (rt_err("fio_png_read_name() error"));
	}
	*texture = tmp;
	return (0);
}

int				fio_png_read(t_txr **texture, char *filename)
{
	t_txr			*tmp;

	if (texture == NULL || filename == NULL)
		return (rt_err("fio_png_read_name(): fatal: given NULL pointer"));
	if (txr_init_default(&tmp, ft_strdup(filename)))
		return (rt_err("fio_png_read_name(): fatal: malloc error"));
	tmp->filename = filename;
	if (png_read(tmp))
	{
		txr_deinit(tmp);
		return (rt_err("fio_png_read() error"));
	}
	*texture = tmp;
	return (0);
}
