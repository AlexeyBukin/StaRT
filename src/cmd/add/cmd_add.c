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
	//t_msg			res;

	if (parser == NULL)
		return(msg_warn("Given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
        return (msg_warn("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "sphere"))
		return cmd_add_sphere(rt, parser);
	if (ft_str_next_is(str, "plane"))
		return (cmd_add_plane(rt, parser));
	if (ft_str_next_is(str, "cylinder"))
		return (cmd_add_cylinder(rt, parser));
	if (ft_str_next_is(str, "cone"))
		return (cmd_add_cone(rt, parser));
	if (ft_str_next_is(str, "group"))
		return (cmd_add_group(rt, parser));
	if (ft_str_next_is(str, "camera"))
		return (cmd_add_camera(rt, parser));
	if (ft_str_next_is(str, "material"))
		return (cmd_add_material(rt, parser));
	return (msg_warn("Syntax error: Unknown object type"));
}
