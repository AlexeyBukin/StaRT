/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 08:57:50 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

static gboolean mouse_moved(GtkWidget *widget,GdkEvent *event, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	if (event->type==GDK_MOTION_NOTIFY) {
		GdkEventMotion* e=(GdkEventMotion*)event;
		ft_printf("Coordinates: (%u,%u)\n", (guint)e->x,(guint)e->y);
	}
	return 1;
}

static void
activate (GtkApplication* app,
		  gpointer        user_data)
{
	GtkWidget *window;

	(void)user_data;
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "starRT Editor");
	g_signal_connect (G_OBJECT (window), "motion-notify-event", G_CALLBACK (mouse_moved), NULL);
	gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
	gtk_widget_show_all (window);
}

int				gui_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->app = gtk_application_new ("ru.school-21.start", G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect (rt->app, "activate", G_CALLBACK (activate), NULL) <= 0)
		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
	rt->context = g_main_context_default();
//	if (g_signal_connect (rt->app, "handle", G_CALLBACK (activate), rt) <= 0)
//		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
//	g_application_add_main_option_entries()
	return (0);
}

int				gui_loop(t_rt *rt, int ac, char **av)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	return (g_application_run (G_APPLICATION (rt->app), ac, av));
}

int				gui_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	g_object_unref (rt->app);
	return (0);
}
