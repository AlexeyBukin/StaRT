/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 19:51:22 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg				cmd_add(t_rt *rt, t_parser *parser)
{
	char			*str;
	t_msg			res;

	if (parser == NULL)
		return(msg_warn("Given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
        return (msg_warn("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "sphere"))
	{
		parser->cur += ft_strlen("sphere");
		res = cmd_add_sphere(rt, parser);
	}
	 else if (ft_str_next_is(str, "plane"))
		{
		parser->cur += ft_strlen("plane");
		res = (cmd_add_plane(rt, parser));
	}
	 else if (ft_str_next_is(str, "cylinder"))
	 {
		parser->cur += ft_strlen("cylinder");
		res = (cmd_add_cylinder(rt, parser));
	 }
	 else if (ft_str_next_is(str, "cone"))
	 {
		parser->cur += ft_strlen("cone");
		res = (cmd_add_cone(rt, parser));
	 }
	else if (ft_str_next_is(str, "group"))
	{
		parser->cur += ft_strlen("group");
		res = (cmd_add_group(rt, parser));
	}
	else
		return (msg_warn("Syntax error: Unknown object type"));
	if (res.status != MSG_OK)
		return (res);
	scn_add_to_group(rt->scene, parser->group, parser->object);
	return (msg_oks("oks"));
}
