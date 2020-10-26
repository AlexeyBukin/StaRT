/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 16:25:06 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTS_H
# define RTS_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"

typedef struct		s_scn
{
	int						id;
	device struct s_obj		*objects;
	int						objects_num;
	device struct s_mat		*materials;
	int						materials_num;
	struct s_cam			camera;
}					t_scn;

typedef struct		s_texture
{
	int					width;
	int					height;
	int					stride;
	t_texture_rgba		*data;
}					t_texture;

typedef struct		s_rt
{
	GtkApplication		*app;
	t_gpu				gpu;
	t_scene				*scene;
	t_texture			*render_result;
}					t_rt;

#endif
