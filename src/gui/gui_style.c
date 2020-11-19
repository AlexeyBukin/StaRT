/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/11/18 18:41:44 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

static void		gui_style(GtkWidget *widget)
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
								const gchar *name, int style)
{
	GObject	*obj;

	obj = gtk_builder_get_object(builder, name);
	if (style == PERSONAL)
		gtk_widget_set_name(GTK_WIDGET(obj), name);
	gui_style(GTK_WIDGET(obj));
	return (obj);
}