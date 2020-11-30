/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgt_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LGT_TYPES_H
# define LGT_TYPES_H

# include "libnum.h"

typedef enum				s_lgt_type
{
	LGT_POINT,
	LGT_PARALLEL
}							t_lgt_type;

typedef struct				s_lgt
{
	t_num					intensity;
	t_vec3					color;
}							t_lgt;

#endif
