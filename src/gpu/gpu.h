/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:34:51 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_H
# define GPU_H

# include "gpu_types.h"
# include "mtl.h"
# include "vlk.h"

int		gpu_init(t_gpu **gpu);
int		gpu_deinit(t_gpu *gpu);

int		gpu_buffer_load(t_gpu *gpu);
int		gpu_kernel_run(t_gpu *gpu);

int 	gpu_buffer_objects_init(t_gpu *gpu, t_scn *scn);
int		gpu_buffer_object_container(t_gpu *gpu, t_obj *obj, t_tfm *global);
int 	gpu_buffer_objects_fill_rec(t_gpu *gpu, t_obj *obj, t_tfm *global);

int		gpu_render(t_rt *rt);

#endif
