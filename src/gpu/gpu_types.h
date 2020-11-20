/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_TYPES_H
# define GPU_TYPES_H

# include "rt_types.h"
# include "gpu_objects.h"
# include "obj_types.h"
# include "mtl.h"
# include "vlk.h"

typedef union		u_gpu_device
{
	t_mtl			*mtl;
	t_vlk			*vlk;
}					t_gpu_dev;

typedef struct		s_gpu
{
	t_gpu_dev		dev;
	t_gpu_obj		*obj_buf;
	size_t			obj_num;
	size_t			obj_current;
}					t_gpu;

#endif
