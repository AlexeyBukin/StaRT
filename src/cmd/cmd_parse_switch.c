/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_switch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 05:21:03 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 10:46:16 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					cmd_str_next_is(char **source, char *word)
{
	if (source == NULL || word == NULL)
		return (0);
	if (*source == NULL)
		return (0);
	if (ft_str_next_is(*source, word))
	{
		*source += ft_strlen(word);
		return (1);
	}
	return (0);
}

int					cmd_parse_switch_1(char **source, t_comp_switch *helper)
{
	if (source == NULL || helper == NULL)
		return (rt_err("Given pointer is NULL"));
	if (*source == NULL)
		return (rt_err("Dereference to NULL"));
	if (cmd_str_next_is(source, KW_CYLINDER))
	{
		helper.type = COMPONENT_OBJECT;
		helper.component.obj = OBJ_CYLINDER;
	}
	else if (cmd_str_next_is(source, KW_MATERIAL))
	{
		helper.type = COMPONENT_MATERIAL;
		helper.component.obj = 0;
	}
	// else if (cmd_str_next_is(source, KW_CAMERA))
	// {
	// 	helper.type = COMPONENT_OBJECT;
	// 	helper.component.obj = OBJ_CONE;
	// }
	// else if (cmd_str_next_is(source, KW_GROUP))
	// {
	// 	helper.type = COMPONENT_OBJECT;
	// 	helper.component.obj = OBJ_CYLINDER;
	// }
	else
		return (rt_warning("Unknown keyword", 1));
}

int					cmd_parse_switch(char **source, t_comp_switch *helper)
{
	if (source == NULL || helper == NULL)
		return (rt_err("Given pointer is NULL"));
	if (*source == NULL)
		return (rt_err("Dereference to NULL"));
	if (cmd_str_next_is(source, KW_PLANE))
	{
		helper.type = COMPONENT_OBJECT;
		helper.component.obj = OBJ_PLANE;
	}
	else if (cmd_str_next_is(source, KW_SPHERE))
	{
		helper.type = COMPONENT_OBJECT;
		helper.component.obj = OBJ_SPHERE;
	}
	else if (cmd_str_next_is(source, KW_CONE))
	{
		helper.type = COMPONENT_OBJECT;
		helper.component.obj = OBJ_CONE;
	}
	else
		return (cmd_parse_switch_1(source, helper));
	return (0);
}
