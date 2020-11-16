/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCN_TYPES_H
# define SCN_TYPES_H

# include "libnum.h"
# include "scn_id.h"
# include "txr_types.h"
# include "mat_types.h"
# include "obj_types.h"
# include "cam_types.h"

typedef struct		s_scn
{
	char			*filename;
	t_obj			*main_group;
	t_cam			*camera_active;
	t_mat			**materials;
	size_t			materials_num;
	t_cam			**cameras;
	size_t			cameras_num;
	t_txr			**textures;
	size_t			textures_num;
//	t_mdl			**models;
//	size_t			models_num;
}					t_scn;

#endif
