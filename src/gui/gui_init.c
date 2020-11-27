/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/26 17:28:53 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

static void		activate(GtkApplication* app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	GtkBuilder 				*builder;
	GObject 				*list_box;

	(void)user_data;
	(void)app;

	if (!(builder = gui_create_builder()))
		return ;
	window = (GtkApplicationWindow *)gui_get_info_and_style(
								builder, "AppWindow", GENERAL, NULL);
	gui_style_for_menu_bar(builder);
	gui_get_info_and_style(builder, "paned", GENERAL, NULL);
	list_box = gui_get_info_and_style(builder, "list_box_all", GENERAL, NULL);
	// gui_get_info_and_style(builder, "list_box_scene", GENERAL, NULL);
	gui_add_widgets_to_list(GTK_LIST_BOX(list_box), user_data, OBJECT);
	// /*list_box = */gui_get_info_and_style(builder, "list_box_light", GENERAL, NULL);
	// gui_add_widgets_to_list(GTK_LIST_BOX(list_box), user_data, LIGHT);
	// gui_get_info_and_style(builder, "box_objs", GENERAL, NULL);
	// gui_get_info_and_style(builder, "box_light", GENERAL, NULL);
	// gui_get_info_and_style(builder, "obj1_scene", GENERAL, NULL);
	// gui_get_info_and_style(builder, "obj2_scene", GENERAL, NULL);
	// gui_get_info_and_style(builder, "obj3_scene", GENERAL, NULL);
	// gui_get_info_and_style(builder, "obj4_scene", GENERAL, NULL);
	// new_func();
	// g_signal_connect(G_OBJECT(window), "button-press-event",
	// 				G_CALLBACK(on_click), signal);
	gui_signals(window, builder, user_data);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
}

int				gui_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->app = gtk_application_new("ru.school-21.start",
									G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect(rt->app, "activate",
							G_CALLBACK(activate), rt) <= 0)
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
