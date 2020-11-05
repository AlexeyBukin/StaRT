/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:44:29 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 14:47:45 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_TYPES_H
# define GPU_TYPES_H

# include "rt_types.h"
# include "mtl.h"
# include "vlk.h"

typedef union		u_gpu
{
	t_mtl			*mtl;
	t_vlk			*vlk;
}					t_gpu;

#endif
