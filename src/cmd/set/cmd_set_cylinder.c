/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:28:42 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 07:46:14 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_set_cylinder_pos(char **source, t_cylinder *cyl)
{
	if (source == NULL || cyl == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(cyl->pos)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set cylinder position"));
}

t_msg					cmd_set_cylinder_cap(char **source, t_cylinder *cyl)
{
	if (source == NULL || cyl == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(cyl->cap)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set cylinder cap"));
}

t_msg					cmd_set_cylinder_radius(char **source, t_cylinder *cyl)
{
	if (source == NULL || cyl == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_num(source, &(cyl->r)))
		return (msg_warn("Syntax error: expected num"));
	return (msg_oks("Set cylinder radius"));
}

t_msg					cmd_set_cylinder(t_scn *scn, t_obj *cylinder, char **source)
{
	t_msg				tmp;
	
	if (scn == NULL || cylinder == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	while (*source != '\0' && *source != '\n')
	{
		tmp = cmd_set_object_param(scn, cylinder, source);
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
			tmp = cmd_set_cylinder_pos(source, &(cylinder->shape.cylinder));
		}
		else if (ft_str_next_is(*source, KW_PARAM_CAP))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_cylinder_cap(source, &(cylinder->shape.cylinder));
		}
		else if (ft_str_next_is(*source, KW_PARAM_RAD))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_cylinder_radius(source, &(cylinder->shape.cylinder));
		}
		else
			return (msg_warn("Unknown flag"));
		if (tmp.status != MSG_OK)
			return (tmp);
		ft_free(tmp.str);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Cylinder parameters set"));
}
