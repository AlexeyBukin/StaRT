/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:54:19 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/07 16:25:33 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_TYPES_H
# define GUI_TYPES_H

# include "rt_types.h"

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

typedef struct		s_gui
{
	struct	s_rt 		*rt_link;
	GtkApplication		*app;
	GMainContext		*context;
	GtkBuilder			*builder;
	GtkWindow			*window;
}					t_gui;

#endif
