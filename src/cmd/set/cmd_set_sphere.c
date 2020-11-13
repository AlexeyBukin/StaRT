/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:44:09 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 07:38:13 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_set_sphere_pos(char **source, t_sphere *sphere)
{
	if (source == NULL || sphere == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(sphere->pos)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set sphere position"));
}

t_msg					cmd_set_sphere_radius(char **source, t_sphere *sphere)
{
	if (source == NULL || sphere == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_num(source, &(sphere->r)))
		return (msg_warn("Syntax error: expected num"));
	return (msg_oks("Set sphere radius"));
}

t_msg					cmd_set_sphere(t_scn *scn, t_obj *sphere, char **source)
{
	t_msg				tmp;
	
	if (scn == NULL || sphere == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	while (*source != '\0' && *source != '\n')
	{
		tmp = cmd_set_object_param(scn, sphere, source);
		if (tmp.status == MSG_ERROR || tmp.status == MSG_WARN)
			return (tmp);
		//TODO concat, dont free
		if (tmp.status == MSG_OK)
		{
			ft_free(tmp.str);
			continue ;
		}
		
		//here only if tmp.status is MSG_NONE
		
		if (ft_str_next_is(*source, KW_PARAM_POS))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_sphere_pos(source, &(sphere->shape.sphere));
		}
		else if (ft_str_next_is(*source, KW_PARAM_RAD))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_sphere_radius(source, &(sphere->shape.sphere));
		}
		else
			return (msg_warn("Unknown flag"));
		if (tmp.status != MSG_OK)
			return (tmp);
		ft_free(tmp.str);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Sphere parameters set"));
}

