/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:33:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 18:26:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <gtk/gtk.h>
# include "libft.h"
# include "err.h"
# include "rts.h"
# include "rt_scene.h"
# include "gui.h"
# include "gpu.h"

int				rt_init(t_rt **rt);
int				rt_deinit(t_rt *rt);

#endif
