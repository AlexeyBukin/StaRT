/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:33:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 21:39:54 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <gtk/gtk.h>
# include "libft.h"
# include "err.h"
# include "rt_types.h"
# include "gui.h"
# include "gpu.h"
# include "srv.h"
# include "scn.h"
# include "cmd.h"
# include "tfm.h"
# include "obj.h"
# include "mat.h"
# include "cam.h"
# include "txr.h"
# include "shp.h"

//# define PLATFORM_MACOS

int				rt_init(t_rt **rt);
int				rt_deinit(t_rt *rt);

#endif
