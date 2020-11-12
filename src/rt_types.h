/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:12:14 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTS_H
# define RTS_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"
# include "srv_types.h"
# include "scn_types.h"
# include "gui_types.h"

typedef struct		s_texture
{
	int					index;
	int					width;
	int					height;
	int					stride;
	t_texture_rgba		*data;
}					t_texture;

typedef struct		s_rt
{
	GtkApplication		*app;
	GMainContext		*context;
	GMutex				mutex_true;
	GMutex				*mutex;
	GThread				*server_thread;
	t_gpu				gpu;
	t_scn				*scene;
	t_texture			*render_result;
	t_srv				*server;
}					t_rt;

#endif
