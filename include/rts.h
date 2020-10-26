/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 18:22:36 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTS_H
# define RTS_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"
# include "rt_scene.h"

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
	t_gpu				gpu;
	t_scn				*scene;
	t_texture			*render_result;
}					t_rt;

#endif
