/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/12/01 21:20:46 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

void			gui_on_server_up(GObject *signal, GtkWindow *parent)
{
	GtkWidget *dialog, *label, *content_area;
	GtkDialogFlags flags;
	(void)signal;

	// Create the widgets
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_dialog_new_with_buttons ("Message",
										parent,
										flags,
										"Shutdown server",
										GTK_RESPONSE_NONE,
										NULL);
	
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	label = gtk_label_new("Server is running...");
	g_signal_connect_swapped (dialog,
							"response",
							G_CALLBACK (gtk_widget_destroy),
							dialog);
	gtk_container_add(GTK_CONTAINER (content_area), label);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
	gtk_widget_show_all (dialog);
}

void			gui_style(GtkWidget *widget)
{
	GtkStyleContext	*context;
	GtkCssProvider	*provider;

	context = gtk_widget_get_style_context(widget);
	provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider,
									 RT_GTK_THEME, NULL);
	gtk_style_context_add_provider(context,
									GTK_STYLE_PROVIDER(provider),
									GTK_STYLE_PROVIDER_PRIORITY_USER);
}

GObject			*gui_get_info_and_style(GtkBuilder *builder,
								const gchar *name_id, int style, gchar *name)
{
	GObject	*obj;

	obj = gtk_builder_get_object(builder, name_id);
	if (style == PERSONAL)
		gtk_widget_set_name(GTK_WIDGET(obj), name);
	gui_style(GTK_WIDGET(obj));
	return (obj);
}

void			gui_style_for_menu_bar(GtkBuilder *builder, GtkApplicationWindow *parent)
{
	GObject *signal;
	
	gui_get_info_and_style(builder, "menu_bar", GENERAL, NULL);
	gui_get_info_and_style(builder, "menu_file", GENERAL, NULL);
	gui_get_info_and_style(builder, "menu_edit", GENERAL, NULL);
	gui_get_info_and_style(builder, "menu_view", GENERAL, NULL);
	gui_get_info_and_style(builder, "menu_help", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_File", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_Edit", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_View", GENERAL, NULL);
	gui_get_info_and_style(builder, "item_Help", GENERAL, NULL);
	gui_get_info_and_style(builder, "menuitem_submenu_1", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_2", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_3", PERSONAL, "submenu");
	signal = gui_get_info_and_style(builder, "menuitem_submenu_4", PERSONAL, "submenu");
	g_signal_connect(signal, "activate",
									G_CALLBACK(gui_on_server_up), GTK_WINDOW(parent));
	gui_get_info_and_style(builder, "menuitem_submenu_5", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_6", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_7", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_8", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_9", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "quit", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "render", PERSONAL, "submenu");
}