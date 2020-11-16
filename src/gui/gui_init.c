/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 18:34:13 by rtacos           ###   ########.fr       */
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

static void		on_render_rt(t_rt *user_data, GtkBuilder *builder)
{
	(void)user_data;
	GdkPixbuf *pix_buf;
	GtkImage *image;

	image = (GtkImage *)gtk_builder_get_object(builder, "image");
	guchar *img = NULL;
	create_img(&img);
	pix_buf = gdk_pixbuf_new_from_data(img, GDK_COLORSPACE_RGB, 0, 8, 700, 50, 700 * 3, NULL, NULL);
	// put_pixel(pix_buf, )
	gtk_image_set_from_pixbuf(image, pix_buf);
	// gtk_image_set_from_file(image, "/Users/rtacos/Desktop/rt_git/res/missing-image-icon-24.png");
}

static void		activate(GtkApplication* app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	// GtkWidget	*button_esc;

	(void)user_data;
	(void)app;

	// window = gtk_application_window_new(app);
	// gtk_window_set_title(GTK_WINDOW(window), "starRT Editor");
	// g_signal_connect(G_OBJECT(window), "motion-notify-event",
	// 								G_CALLBACK(mouse_moved), NULL);
	// gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
	// gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);

	// button_esc = gtk_button_new();
	// button_esc = gtk_button_new_with_label("Exit");
	// gtk_container_add(GTK_CONTAINER(window), button_esc);

	// create_a_scene_table(window);
	
	
	GtkBuilder *builder;
	//   GtkWidget *window;
	// GObject *button;
	GError *error = NULL;
	
	// GtkWidget *butbox;
	// butbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

	/* Construct a GtkBuilder instance and load our UI description */
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file(builder, "src/gui/ui/builder.ui", &error) == 0)
	{
		g_printerr ("Error loading file: %s\n", error->message);
		g_clear_error (&error);
		return ;
	}
	/* Connect signal handlers to the constructed widgets. */
	window = (GtkApplicationWindow *)gtk_builder_get_object(builder, "AppWindow");
	gtk_widget_set_name((GtkWidget *)window, "AppWindow");
	gui_style((GtkWidget *)window);
	g_signal_connect(G_OBJECT(window), "destroy",
									G_CALLBACK(gtk_main_quit), NULL);

	GtkMenuBar *menu_bar = (GtkMenuBar *)gtk_builder_get_object(builder, "menu_bar");
	gtk_widget_set_name((GtkWidget *)menu_bar, "menu_bar");
	gui_style((GtkWidget *)menu_bar);

	GtkPaned *paned = (GtkPaned *)gtk_builder_get_object(builder, "paned");
	gtk_widget_set_name((GtkWidget *)paned, "paned");
	gui_style((GtkWidget *)paned);

	GtkListBox *list_box = (GtkListBox *)gtk_builder_get_object(builder, "list_box");
	gtk_widget_set_name((GtkWidget *)list_box, "list_box");
	gui_style((GtkWidget *)list_box);

	GObject *signal;
	signal = gtk_builder_get_object(builder, "quit");
	g_signal_connect(signal, "activate",
					G_CALLBACK(gtk_main_quit), NULL);
	signal = gtk_builder_get_object(builder, "render");
	g_signal_connect(signal, "activate",
					G_CALLBACK(on_render_rt), (GtkBuilder *)builder);
	// g_signal_connect(G_OBJECT(window), "motion-notify-event",
	// 						G_CALLBACK(mouse_moved), NULL);

	// gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
	// gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);


	// button = gtk_builder_get_object(builder, "button1");
	// g_signal_connect((GtkWidget *)button, "clicked", G_CALLBACK(print_hello), NULL);
	// gtk_widget_set_name((GtkWidget *)button, "button");
	// style((GtkWidget *)button);

	// button = gtk_builder_get_object(builder, "button2");
	// g_signal_connect((GtkWidget *)button, "clicked", G_CALLBACK(print_hello), NULL);
	// gtk_widget_set_name((GtkWidget *)button, "button2");
	// style((GtkWidget *)button);

	// button = gtk_builder_get_object(builder, "quit");
	// g_signal_connect((GtkWidget *)button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	// gtk_widget_set_name((GtkWidget *)button, "button");
	// style((GtkWidget *)button);
	// gtk_widget_set_name((GtkWidget *)butbox, "button");
	gtk_widget_show_all((GtkWidget *)window);
	gtk_main ();
}

int				gui_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->app = gtk_application_new("ru.school-21.start",
									G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect(rt->app, "activate",
							G_CALLBACK(activate), NULL) <= 0)
		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
//	if (g_signal_connect (rt->app, "handle", G_CALLBACK (activate), rt) <= 0)
//		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
//	g_application_add_main_option_entries()
	return (0);
}

int				gui_loop(t_rt *rt, int ac, char **av)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	return (g_application_run(G_APPLICATION (rt->app), ac, av));
}

int				gui_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	g_object_unref(rt->app);
	return (0);
}
