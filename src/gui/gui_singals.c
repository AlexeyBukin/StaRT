/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_singals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/07 16:29:19 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

static void		create_img(guchar **img)
{
	int count = 35000 * 3;
	// int count = 3000;
	*img = (guchar*)ft_memalloc(count);
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 700; j++)
		{
			guchar *def = &((*img)[i * 700 * 3 + j * 3]);// = (255 << 24) | (255 << 16);
			guchar perc_r = 255 * i / 50;
			guchar perc_b = 255 * j / 700;
			def[0] = (guchar)perc_r;
			def[1] = 0;
			def[2] = (guchar)perc_b;
			// def[3] = 255;
		}
	}
}

void		on_render_rt(GObject *obj, t_rt *user_data)
{
	(void)obj;
	GdkPixbuf *pix_buf;
	GtkImage *image;

	image = (GtkImage *)gtk_builder_get_object(user_data->gui->builder,
											"image");
	guchar *img = NULL;
	create_img(&img);
	pix_buf = gdk_pixbuf_new_from_data(img, GDK_COLORSPACE_RGB,
							0, 8, 700, 50, 700 * 3, NULL, NULL);
	gtk_image_set_from_pixbuf(image, pix_buf);
	// gtk_image_set_from_file(image, "/Users/rtacos/Desktop/rt_git/res/missing-image-icon-24.png");
}

void			gui_on_server_up(GObject *signal, t_rt *user_data)
{
	GtkWidget		*dialog;
	GtkWidget		*label;
	GtkWidget		*content_area;
	GtkDialogFlags	flags;
	(void)signal;

	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_dialog_new_with_buttons("Message", user_data->gui->window,
						flags, "Shutdown server", GTK_RESPONSE_NONE, NULL);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new("Server is running...");
	g_signal_connect_swapped(dialog, "response",
						G_CALLBACK(gtk_widget_destroy), dialog);
	gtk_container_add(GTK_CONTAINER(content_area), label);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), user_data->gui->window);
	gtk_widget_show_all(dialog);
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
	signal = gtk_builder_get_object(builder, "server_up");
	user_data->gui->window = GTK_WINDOW(window);
	g_signal_connect(signal, "activate",
					G_CALLBACK(gui_on_server_up), user_data);
	// free(data);
}