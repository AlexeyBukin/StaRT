/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 05:21:03 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 06:21:36 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

# define CMD_SET_NUM 5


t_msg					cmd_set_sphere(t_rt *rt, char *source)

t_msg					cmd_set(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_SET_NUM] = {
		(t_parse_fw){&cmd_set_sphere, KW_SPHERE},
		(t_parse_fw){&cmd_set_plane, KW_PLANE},
		(t_parse_fw){&cmd_set_cylinder, KW_CYLINDER},
		(t_parse_fw){&cmd_set_cone, KW_CONE},
		(t_parse_fw){&cmd_set_material, KW_MATERIAL}
		// (t_parse_fw){&cmd_set_camera, KW_CAMERA}
	};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_SET_NUM));
}

