/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/30 21:24:13 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

static void		activate(GtkApplication* app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	GtkBuilder 				*builder;
	GtkTreeView				*tree_view;
	GtkTreeViewColumn		*col;
	GtkWidget				*label;
	(void)app;

	if (!(builder = gui_create_builder()))
		return ;
	window = (GtkApplicationWindow *)gui_get_info_and_style(
								builder, "AppWindow", GENERAL, NULL);
	gui_style_for_menu_bar(builder);
	gui_get_info_and_style(builder, "paned", GENERAL, NULL);
	GtkTreeStore *store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	tree_view = GTK_TREE_VIEW(gui_get_info_and_style(builder, "tree_view", GENERAL, NULL));
	gtk_tree_view_set_model(tree_view, GTK_TREE_MODEL(store));
	gui_add_widgets_to_tree(store, user_data, OBJECT);
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	// gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view),
    //                                             COLUMN_TITLE,
    //                                             "Title", renderer,
    //                                             "text", COLUMN_TITLE,
    //                                             NULL);
	col = gtk_tree_view_column_new();
	label = gtk_label_new("");
	gui_style(label);
	gtk_tree_view_column_set_widget(col, label);
	// renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(col, renderer, TRUE);
	gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN_TITLE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), col);
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree_view), 0);
	label = gtk_tree_view_column_get_widget(col);
	gtk_widget_show(label);
  label = gtk_widget_get_parent (label); /* the alignment */
  /* set_color (w, color); NOK*/

  label = gtk_widget_get_parent (label); /* the hbox */
  /* set_color (w, color); NOK*/

  label = gtk_widget_get_parent (label); /* the button */
	gui_style(label);
	gui_get_info_and_style(builder, "item_File", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_Edit", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_View", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_Help", GENERAL, NULL);
	gui_signals(window, builder, user_data);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
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