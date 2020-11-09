/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:44:09 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/10 00:33:12 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_msg					cmd_set_sphere_pos(char **source, t_sphere *sphere)
{
	t_msg				result;

	if (source == NULL || sphere == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	result = (t_msg){"Set sphere position", MSG_OK};
	if (cmd_read_vec())
	return (result);
}

t_msg					cmd_set_sphere_radius(char **source, t_sphere *sphere)
{
	t_msg				result;
	
	result = (t_msg){"Added sphere", MSG_OK};
	
	return (result);
}

t_msg					cmd_set_sphere_material(char **source, t_sphere *sphere)
{
	t_msg				result;

	result = (t_msg){"Added sphere", MSG_OK};

	return (result);
}

t_msg					cmd_set_sphere_name(char **source, t_sphere *sphere)
{
	t_msg				result;

	result = (t_msg){"Added sphere", MSG_OK};

	return (result);
}
