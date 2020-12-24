/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:07:40 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"
# include "srv_types.h"
# include "scn_types.h"
# include "cmd_types.h"
# include "gui_types.h"
# include "txr_types.h"
# include "mat_types.h"
# include "gui_types.h"

typedef struct		s_rt
{
	GThread				*server_thread;
	t_gpu				*gpu;
	t_scn				*scene;
	t_txr				*render_result;
	t_srv				*server;
	t_gui				*gui;
}					t_rt;

#endif
