/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/11/26 17:28:22 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

void				gui_style(GtkWidget *widget)
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

GObject				*gui_get_info_and_style(GtkBuilder *builder,
								const gchar *name_id, int style, gchar *name)
{
	GObject			*obj;

	obj = gtk_builder_get_object(builder, name_id);
	if (style == PERSONAL)
		gtk_widget_set_name(GTK_WIDGET(obj), name);
	gui_style(GTK_WIDGET(obj));
	return (obj);
}

void				gui_style_for_menu_bar(GtkBuilder *builder)
{
	GtkHeaderBar	*header;

	header = GTK_HEADER_BAR(
		gui_get_info_and_style(builder, "header_bar", GENERAL, NULL));
	gtk_header_bar_set_show_close_button(header, TRUE);
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
	gui_get_info_and_style(builder, "menuitem_submenu_4", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_5", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_6", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_7", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_8", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "menuitem_submenu_9", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "quit", PERSONAL, "submenu");
	gui_get_info_and_style(builder, "render", PERSONAL, "submenu");
}