/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/07 20:33:48 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

// enum
//   {
//     COL_ICON = 0,
//     COL_TEXT,
//     NUM_COLS
//   };

//   GtkListStore *create_liststore(void)
//   {
//     GtkListStore  *store;
//     GtkTreeIter    iter;
//     GdkPixbuf     *icon;
//     GError        *error = NULL;

//     store = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

//     icon = gdk_pixbuf_new_from_file("icon.png", &error);
//     if (error)
//     {
//       g_warning ("Could not load icon: %s\n", error->message);
//       g_error_free(error);
//       error = NULL;
//     }

//     gtk_list_store_append(store, &iter);
//     gtk_list_store_set(store, &iter,
//                        COL_ICON, icon,
//                        COL_TEXT, "example",
//                        -1);

//     return store;
//   }

//   GtkWidget *create_treeview(void)
//   {
//     GtkTreeModel      *model;
//     GtkTreeViewColumn *col;
//     GtkCellRenderer   *renderer;
//     GtkWidget         *view;

//     model = GTK_TREE_MODEL(create_liststore());

//     view = gtk_tree_view_new_with_model(model);

//     col = gtk_tree_view_column_new();
//     gtk_tree_view_column_set_title(col, "Title");

//     renderer = gtk_cell_renderer_pixbuf_new();
//     gtk_tree_view_column_pack_start(col, renderer, FALSE);
//     gtk_tree_view_column_set_attributes(col, renderer,
//                                         "pixbuf", COL_ICON,
//                                         NULL);

//     renderer = gtk_cell_renderer_text_new();
//     gtk_tree_view_column_pack_start(col, renderer, TRUE);
//     gtk_tree_view_column_set_attributes(col, renderer,
//                                         "text", COL_TEXT,
//                                         NULL);

//     gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

//     gtk_widget_show_all(view);

//     return view;
//   }

// void			quick_message(GtkWindow *parent, gchar *message)
// {
//  GtkWidget *dialog, *label, *content_area;
//  GtkDialogFlags flags;

//  // Create the widgets
//  flags = GTK_DIALOG_DESTROY_WITH_PARENT;
//  dialog = gtk_dialog_new_with_buttons ("Message",
//                                        parent,
//                                        flags,
//                                        _("_OK"),
//                                        GTK_RESPONSE_NONE,
//                                        NULL);
//  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
//  label = gtk_label_new (message);

//  // Ensure that the dialog box is destroyed when the user responds

//  g_signal_connect_swapped (dialog,
//                            "response",
//                            G_CALLBACK (gtk_widget_destroy),
//                            dialog);

//  // Add the label, and show everything we’ve added

//  gtk_container_add (GTK_CONTAINER (content_area), label);
//  gtk_widget_show_all (dialog);
// }

static void		activate(GtkApplication* app, t_rt *user_data)
{
	GtkApplicationWindow	*window;
	GtkBuilder 				*builder;
	(void)app;

	if (!(builder = gui_create_builder()))
		return ;
	window = (GtkApplicationWindow *)gui_get_info_and_style(
								builder, "AppWindow", GENERAL, NULL);
	gui_style_for_menu_bar(builder);
	gui_get_info_and_style(builder, "paned", GENERAL, NULL);
	// gui_create_gtk_tree(builder, user_data);
	// gui_get_info_and_style(builder, "item_Edit", GENERAL, NULL);
	// gui_get_info_and_style(builder, "item_View", GENERAL, NULL);
	// gui_get_info_and_style(builder, "item_Help", GENERAL, NULL);
	gui_signals(window, builder, user_data);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();

// # define TOGGLE_SERVER_ON  "Click to start server"
// # define TOGGLE_SERVER_OFF "Click to stop server"

// static void button_server_clicked (GtkButton *source, t_rt *rt) {
// 	if (source == NULL || rt == NULL)
// 	{
// 		rt_err("Cannot start server");
// 		return ;
// 	}

// //	gboolean  is_active = gtk_toggle_button_get_active(source);
// 	if (rt->server == NULL)
// 	{
// 		if (srv_init(rt))
// 			rt_err("Cannot start server");
// 		else
// 		{
// 			gtk_button_set_label(GTK_BUTTON(source), TOGGLE_SERVER_OFF);
// 		}
// 	}
// 	else
// 	{
// 		if (srv_deinit(rt))
// 			rt_err("Cannot stop server");
// 		else
// 		{
// 			gtk_button_set_label(GTK_BUTTON(source), TOGGLE_SERVER_ON);
// 		}
// 	}
// }

// static void activate (GtkApplication* app, t_rt *rt)
// {
// 	GtkWidget *button_server;
// 	GtkWidget *window;

// 	window = gtk_application_window_new (app);
// 	gtk_window_set_title (GTK_WINDOW (window), "StarRT Editor");
// 	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

// 	{
// 		button_server = gtk_button_new_with_label (TOGGLE_SERVER_ON);
// 		g_signal_connect (button_server, "clicked", G_CALLBACK (button_server_clicked), rt);
// 		gtk_container_add (GTK_CONTAINER (window), button_server);
// 	}

// 	gtk_widget_show_all (window);
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
	gui->app = gtk_application_new ("ru.school-21.start", G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect (gui->app, "activate", G_CALLBACK (activate), rt) <= 0)
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
	return (g_application_run(G_APPLICATION (rt->gui->app), ac, av));
}

int				gui_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	g_object_unref(rt->gui->app);
	return (0);
}
