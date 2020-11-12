/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:18:38 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/11 11:42:23 by jvoor            ###   ########.fr       */
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
		return (msg_err("Syntax error: expected num"));
	return (msg_oks("Set plane distance"));
}

t_msg					cmd_set_plane_material(char **source, t_plane *plane)
{
	(void)source;
	(void)plane;
	t_msg				result;

	result = msg_oks("Added plane");

	return (result);
}

t_msg					cmd_set_plane_name(char **source, t_plane *plane)
{
	(void)source;
	(void)plane;
	t_msg				result;

	result = msg_oks("Added plane");

	return (result);
}

