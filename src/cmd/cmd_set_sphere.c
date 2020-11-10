/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:44:09 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/10 04:57:35 by kcharla          ###   ########.fr       */
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
		return (msg_err("Syntax error: expected num"));
	return (msg_oks("Set sphere radius"));
}

t_msg					cmd_set_sphere_material(char **source, t_sphere *sphere)
{
	(void)source;
	(void)sphere;
	t_msg				result;

	result = msg_oks("Added sphere");

	return (result);
}

t_msg					cmd_set_sphere_name(char **source, t_sphere *sphere)
{
	(void)source;
	(void)sphere;
	t_msg				result;

	result = msg_oks("Added sphere");

	return (result);
}
