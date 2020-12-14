/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_gtk_tree_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/08 17:23:41 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		gui_creating_and_rendering_columns(GtkTreeView *tree_view)
{
	GtkCellRenderer			*renderer;
	GtkTreeViewColumn		*col;
	GtkWidget				*label;

	renderer = gtk_cell_renderer_text_new();
	col = gtk_tree_view_column_new();
	label = gtk_label_new("What will be written above the group with objects");
	gtk_tree_view_column_set_widget(col, label);
	gtk_tree_view_column_pack_start(col, renderer, TRUE);
	gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN_TITLE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), col);
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree_view), 0);
	label = gtk_tree_view_column_get_widget(col);
	gtk_widget_show(label);
	label = gtk_widget_get_parent(label);
	label = gtk_widget_get_parent(label);
	label = gtk_widget_get_parent(label);
	gui_style(label);
}

void			gui_create_gtk_tree(GtkBuilder *builder, t_rt *user_data)
{
	GtkTreeStore			*store;
	GtkTreeView				*tree_view;

	store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING,
								G_TYPE_STRING, G_TYPE_STRING);
	tree_view = GTK_TREE_VIEW(gui_get_info_and_style(builder,
								"tree_view", GENERAL, NULL));
	gtk_tree_view_set_model(tree_view, GTK_TREE_MODEL(store));
	gui_add_widgets_to_tree(store, user_data, OBJECT);
	gui_creating_and_rendering_columns(tree_view);
}
