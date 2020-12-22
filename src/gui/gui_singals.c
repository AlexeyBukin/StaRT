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

void			on_render_rt(GObject *obj, t_rt *rt)
{
	t_txr		*res;
	GdkPixbuf	*pix_buf;
	GtkImage	*image;

	(void)obj;
	rt_warn("on_render_rt(): rendering...");
	// TODO complete render
	if (gpu_render(rt))
	{
		rt_err("on_render_rt(): render fail");
		return ;
	}
	image = (GtkImage *)gtk_builder_get_object(rt->gui->builder, "image");
	res = rt->gpu->render_result;
	pix_buf = gdk_pixbuf_new_from_data(res->content, GDK_COLORSPACE_RGB,
				TRUE, 8, res->width, res->height, res->stride, NULL, NULL);
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
