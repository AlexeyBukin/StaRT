/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/08 17:37:38 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		activate(GtkApplication *app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	GtkBuilder				*builder;

	(void)app;
	if (!(builder = gui_create_builder()))
		return ;
	window = (GtkApplicationWindow *)gui_get_info_and_style(
								builder, "AppWindow", GENERAL, NULL);
	gui_style_for_menu_bar(builder);
	gui_get_info_and_style(builder, "paned", GENERAL, NULL);
	gui_signals(window, builder, user_data);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
}

t_gui			*gui_struct_init(t_rt *rt)
{
	t_gui		*gui;

	if ((gui = (t_gui *)malloc(sizeof(t_gui))))
	{
		rt->gui = gui;
		gui->rt_link = rt;
	}
	return (gui);
}

int				gui_init(t_rt *rt)
{
	t_gui		*gui;

	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (!(gui = gui_struct_init(rt)))
		return (rt_err("Cannot allocation gui struct"));
	gui->app = gtk_application_new("ru.school-21.start",
								G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect(gui->app, "activate", G_CALLBACK(activate), rt) <= 0)
		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
	return (0);
}

int				gui_loop(t_rt *rt, int ac, char **av)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	return (g_application_run(G_APPLICATION(rt->gui->app), ac, av));
}

int				gui_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	g_object_unref(rt->gui->app);
	return (0);
}
