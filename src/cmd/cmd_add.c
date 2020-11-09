/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define KW_PARAM_P "-p"
#define KW_PARAM_R "-r"
#define KW_PARAM_M "-m"

t_msg					cmd_set_sphere_pos(char **source, t_sphere *sphere)
{
	t_msg				result;
	
	result = (t_msg){"Added sphere", MSG_OK};
	
	return (result);
}

t_msg					cmd_add_sphere(t_rt *rt, const char *source)
{
	t_msg				result;
	t_sphere			*sphere;
	
	if (rt == NULL || source == NULL)
		return (msg_err("Entered NULL pointers"));
	result = (t_msg){"Added sphere", MSG_OK};
	sphere = scn_get_obj(rt->scene);
	if (sphere == NULL)
		return (msg_err("Given pointer is NULL"));
	// scn have to init sphere to defaut values
	while (*source != '\0' && *source != '\n' && result.status != MSG_ERROR)
	{
		if (ft_str_next_is(source, KW_PARAM_P))
			result = cmd_set_sphere_pos(&source, sphere);
		else if (ft_str_next_is(source, KW_PARAM_R))
			result = cmd_set_sphere_radius(&source, sphere);
		else if (ft_str_next_is(source, KW_PARAM_M))
			result = cmd_set_sphere_material(&source, sphere);
		else
			result = msg_err("Unknown flag");
	}
	return (result);
}