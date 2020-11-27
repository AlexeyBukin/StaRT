/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/24 16:12:58 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

enum {
    COLUMN_TITLE,
    COLUMN_ARTIST,
    COLUMN_CATALOGUE,
    N_COLUMNS
};

static void		activate(GtkApplication* app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	GtkBuilder 				*builder;
	GtkWidget				*tree_view;

	(void)user_data;
	(void)app;

	if (!(builder = gui_create_builder()))
		return ;
	window = (GtkApplicationWindow *)gui_get_info_and_style(
								builder, "AppWindow", GENERAL);
	gui_get_info_and_style(builder, "menu_bar", GENERAL);
	gui_get_info_and_style(builder, "paned", GENERAL);

	
	GtkTreeStore *store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	GtkTreeIter parent_iter, child_iter;
	tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	gui_get_info_and_style(builder, "tree_view", GENERAL);
	//gtk_tree_view_set_model(tree_view, GTK_TREE_MODEL(store));
	
	gtk_tree_store_append(store, &parent_iter, NULL);
    gtk_tree_store_set(store, &parent_iter,
                       COLUMN_TITLE, "Dark Side of the Moon",
                       COLUMN_ARTIST, "Pink Floyd",
                       COLUMN_CATALOGUE, "B000024D4P",
                       -1);
	gtk_tree_store_append(store, &child_iter, &parent_iter);
    gtk_tree_store_set(store, &child_iter, COLUMN_TITLE, "Speak to Me", -1);

	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree_view),
                                                COLUMN_TITLE,
                                                "Title", renderer,
                                                "text", COLUMN_TITLE,
                                                NULL);
	//gui_add_widgets_to_list(GTK_LIST_BOX(list_box), user_data, OBJECT);

	// /*list_box = */gui_get_info_and_style(builder, "list_box_light", GENERAL);
	// gui_add_widgets_to_list(GTK_LIST_BOX(list_box), user_data, LIGHT);
	// gui_get_info_and_style(builder, "box_objs", GENERAL);
	// gui_get_info_and_style(builder, "box_light", GENERAL);
	// gui_get_info_and_style(builder, "obj1_scene", GENERAL);
	// gui_get_info_and_style(builder, "obj2_scene", GENERAL);
	// gui_get_info_and_style(builder, "obj3_scene", GENERAL);
	// gui_get_info_and_style(builder, "obj4_scene", GENERAL);
	gui_get_info_and_style(builder, "item_File", GENERAL);
	gui_get_info_and_style(builder, "item_Edit", GENERAL);
	gui_get_info_and_style(builder, "item_View", GENERAL);
	gui_get_info_and_style(builder, "item_Help", GENERAL);
	gui_signals(window, builder, user_data);
	gtk_container_add(GTK_CONTAINER(window), tree_view);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main ();
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