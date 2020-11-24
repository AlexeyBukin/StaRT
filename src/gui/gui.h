/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/24 16:12:41 by rtacos           ###   ########.fr       */
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

int				gui_loop(t_rt *rt, int ac, char **av);
int				gui_init(t_rt *rt);
int				gui_deinit(t_rt *rt);
GObject			*gui_get_info_and_style(GtkBuilder *builder,
									const gchar *name, int style);
void			gui_signals(GtkApplicationWindow *window, GtkBuilder *builder,
															t_rt *user_data);
GtkBuilder		*gui_create_builder(void);
void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data,
																int type_box);
void			gui_style(GtkWidget *widget);

#endif
