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

#ifndef GPU_H
# define GPU_H

# include "gpu_types.h"

int				gpu_init(t_gpu **gpu);
int				gpu_deinit(t_gpu *gpu);

int				gpu_buffer_load(t_gpu *gpu);
int				gpu_kernel_run(t_gpu *gpu);

int 			gpu_buffer_objects_init(t_gpu *gpu, t_scn *scn);
int				gpu_buffer_object_container(t_gpu *gpu, t_obj *obj, t_tfm *global);
int 			gpu_buffer_objects_fill_rec(t_gpu *gpu, t_obj *obj, t_tfm *global);

#endif
