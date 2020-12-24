/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/09 18:08:38 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "gui_types.h"
# include <glib.h>

# define RT_GTK_THEME "src/gui/theme.css"

int				gui_loop(t_rt *rt, int ac, char **av);
int				gui_init(t_rt *rt);
int				gui_deinit(t_rt *rt);
GObject			*gui_get_info_and_style(GtkBuilder *builder,
								const gchar *name_id, int style, gchar *name);
void			gui_style(GtkWidget *widget);
void			gui_signals(GtkApplicationWindow *window, GtkBuilder *builder,
														t_rt *user_data);
GtkBuilder		*gui_create_builder(void);
void			gui_add_widgets_to_tree(GtkTreeStore *list_box, t_rt *user_data,
														int type_box);
void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data,
														int type_box);
void			gui_style_for_menu_bar(GtkBuilder *builder);
void			gui_create_gtk_tree(GtkBuilder *builder, t_rt *user_data);

#endif
