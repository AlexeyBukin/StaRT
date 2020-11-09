/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:33:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/04 19:45:45 by kcharla          ###   ########.fr       */
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

//# define PLATFORM_MACOS

int				rt_init(t_rt **rt);
int				rt_deinit(t_rt *rt);

#endif
