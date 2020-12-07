/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/12/07 20:10:24 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

GtkBuilder		*gui_create_builder(void)
{
	GtkBuilder	*builder;
	GError		*error;

	error = NULL;
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, "src/gui/ui/builder.ui", &error))
	{
		g_printerr("Error loading file: %s\n", error->message);
		g_clear_error(&error);
		return (NULL);
	}
	return (builder);
}