/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_singals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/08 17:16:04 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		create_img(guchar **img)
{
	int		count;

	count = 35000 * 3;
	*img = (guchar*)ft_memalloc(count);
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 700; j++)
		{
			guchar *def = &((*img)[i * 700 * 3 + j * 3]);
			guchar perc_r = 255 * i / 50;
			guchar perc_b = 255 * j / 700;
			def[0] = (guchar)perc_r;
			def[1] = 0;
			def[2] = (guchar)perc_b;
		}
	}
}

void			on_render_rt(GObject *obj, t_rt *user_data)
{
	GdkPixbuf	*pix_buf;
	GtkImage	*image;
	guchar		*img;

	(void)obj;
	image = (GtkImage *)gtk_builder_get_object(user_data->gui->builder,
											"image");
	img = NULL;
	create_img(&img);
	pix_buf = gdk_pixbuf_new_from_data(img, GDK_COLORSPACE_RGB,
							0, 8, 700, 50, 700 * 3, NULL, NULL);
	gtk_image_set_from_pixbuf(image, pix_buf);
}

void			gui_signals(GtkApplicationWindow *window, GtkBuilder *builder,
															t_rt *user_data)
{
	GObject		*signal;

	g_signal_connect(G_OBJECT(window), "destroy",
					G_CALLBACK(gtk_main_quit), NULL);
	signal = gtk_builder_get_object(builder, "quit");
	g_signal_connect(signal, "activate",
					G_CALLBACK(gtk_main_quit), NULL);
	signal = gtk_builder_get_object(builder, "render");
	user_data->gui->builder = builder;
	g_signal_connect(signal, "activate",
					G_CALLBACK(on_render_rt), user_data);
	g_signal_connect(G_OBJECT(window), "destroy",
					G_CALLBACK(gtk_main_quit), NULL);
}
