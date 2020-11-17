/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_object_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 05:21:03 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 08:21:25 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO add -N name, -M material, -T tag, -G group

t_msg			cmd_set_object_name(t_scn *scn, t_obj *obj, char **source)
{
	char		*name;
	int			res;
	
	if (scn == NULL || obj == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if ((res = cmd_read_string(source, &name)))
	{
		if (res < 0)
			return (msg_err("Cannot read name string"));
		return (msg_warn("Cannot read name string"));
	}
	if (scn_component_set_name(scn, obj->id, name))
		return (msg_err("Cannot set name"));
	return (msg_oks("Name set"));
}

t_msg			cmd_set_object_material(t_scn *scn, t_obj *obj, char **source)
{
	uint		mat_id;
	
	if (scn == NULL || obj == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if ((res = cmd_read_id_name(scn, source, &mat_id)))
	{
		if (res < 0)
			return (msg_err("Cannot read material"));
		return (msg_warn("Cannot read material"));
	}
	if (scn_check_mid(mat_id))
		return (msg_err("Cannot find material"));
	obj->material_id = mat_id;
	return (msg_oks("Material set"));
}

//TODO add -N name, -M material, -T tag, -G group


t_msg			cmd_set_object_param(t_scn *scn, t_obj *obj, char **source)
{
    if (scn == NULL || obj == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	
    if (ft_str_next_is(*source, KW_PARAM_NAME))
	{
		*source += KW_PARAM_LEN;
		return (cmd_set_object_name(scn, obj, source));
	}
	else if (ft_str_next_is(*source, KW_PARAM_MAT))
	{
		*source += KW_PARAM_LEN;
		return (cmd_set_object_mat(scn, obj, source));
	}
	return ((t_msg)(MSG_NONE, NULL));
}
