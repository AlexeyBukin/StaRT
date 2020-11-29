/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/28 20:14:45 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GUI_H
# define GUI_H

# include "rt_types.h"

# define RT_GTK_THEME "src/gui/theme.css"

enum e_type_box {
	OBJECT,
	LIGHT
};

enum e_styles {
	GENERAL,
	PERSONAL
};

enum {
    COLUMN_TITLE,
    COLUMN_ARTIST,
    COLUMN_CATALOGUE,
    N_COLUMNS
};

int				gui_loop(t_rt *rt, int ac, char **av);
int				gui_init(t_rt *rt);
int				gui_deinit(t_rt *rt);
GObject			*gui_get_info_and_style(GtkBuilder *builder,
									const gchar *name_id, int style, gchar *name);
void			gui_style(GtkWidget *widget);
void			gui_style_for_menu_bar(GtkBuilder *builder);
void			gui_signals(GtkApplicationWindow *window, GtkBuilder *builder,
															t_rt *user_data);
GtkBuilder		*gui_create_builder(void);
void			gui_add_widgets_to_tree(GtkTreeStore *list_box, t_rt *user_data, int type_box);
void			gui_style(GtkWidget *widget);
void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data,
																int type_box);
void			on_render_rt(t_rt *user_data, GtkBuilder *builder);
void			gui_style_for_menu_bar(GtkBuilder *builder);


#endif
