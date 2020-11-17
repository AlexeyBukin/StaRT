/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:18:38 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 07:40:33 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_set_plane_norm(char **source, t_plane *plane)
{
	if (source == NULL || plane == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(plane->n)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set plane normal"));
}

t_msg					cmd_set_plane_dist(char **source, t_plane *plane)
{
	if (source == NULL || plane == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_num(source, &(plane->d)))
		return (msg_warn("Syntax error: expected num"));
	return (msg_oks("Set plane distance"));
}

t_msg					cmd_set_plane(t_scn *scn, t_obj *plane, char **source)
{
	t_msg				tmp;
	
	if (scn == NULL || plane == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	while (*source != '\0' && *source != '\n')
	{
		tmp = cmd_set_object_param(scn, plane, source);
		if (tmp.status == MSG_ERROR || tmp.status == MSG_WARN)
			return (tmp);
		//TODO concat, dont free
		if (tmp.status == MSG_OK)
		{
			ft_free(tmp.str);
			continue ;
		}
		
		//here only if tmp.status is MSG_NONE
		
		if (ft_str_next_is(*source, KW_PARAM_NORM))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_plane_norm(source, &(plane->shape.plane));
		}
		else if (ft_str_next_is(*source, KW_PARAM_DIST))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_plane_dist(source, &(plane->shape.plane));
		}
		else
			return (msg_warn("Unknown flag"));
		if (tmp.status != MSG_OK)
			return (tmp);
		ft_free(tmp.str);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Plane parameters set"));
}
