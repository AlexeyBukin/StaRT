/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 05:01:18 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 07:45:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_set_cone_pos(char **source, t_cone *cone)
{
	if (source == NULL || cone == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(cone->pos)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set cone position"));
}

t_msg					cmd_set_cone_cap(char **source, t_cone *cone)
{
	if (source == NULL || cone == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_vec(source, &(cone->cap)))
		return (msg_warn("Syntax error: expected vector"));
	return (msg_oks("Set cone cap"));
}

t_msg					cmd_set_cone_radius(char **source, t_cone *cone)
{
	if (source == NULL || cone == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	if (cmd_read_num(source, &(cone->r)))
		return (msg_warn("Syntax error: expected num"));
	return (msg_oks("Set cone radius"));
}

t_msg					cmd_set_cone(t_scn *scn, t_obj *cone, char **source)
{
	t_msg				tmp;
	
	if (scn == NULL || cone == NULL || source == NULL)
		return (msg_err("Given pointer is NULL"));
	if (*source == NULL)
		return (msg_err("Dereference to NULL pointer"));
	while (*source != '\0' && *source != '\n')
	{
		tmp = cmd_set_object_param(scn, cone, source);
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
			tmp = cmd_set_cone_pos(source, &(cone->shape.cone));
		}
		else if (ft_str_next_is(*source, KW_PARAM_CAP))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_cone_cap(source, &(cone->shape.cone));
		}
		else if (ft_str_next_is(*source, KW_PARAM_RAD))
		{
			*source += KW_PARAM_LEN;
			tmp = cmd_set_cone_radius(source, &(cone->shape.cone));
		}
		else
			return (msg_warn("Unknown flag"));
		if (tmp.status != MSG_OK)
			return (tmp);
		ft_free(tmp.str);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Cone parameters set"));
}
