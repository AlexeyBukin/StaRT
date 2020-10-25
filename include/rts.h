/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 14:32:00 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTS_H
# define RTS_H

# include <gtk/gtk.h>
# include "libft.h"
# include "mtl.h"
# include "vlk.h"

typedef union		u_gpu
{
	t_mtl			*mtl;
	t_vlk			*vlk;
}					t_gpu;


typedef struct		s_rt
{
	GtkApplication		*app;
	t_gpu				gpu;
}					t_rt;

#endif
