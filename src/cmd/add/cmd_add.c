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

t_msg				cmd_add(t_parser *parser)
{
	char			*str;

	if (parser == NULL)
		return(msg_err("Given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
        return (msg_err("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "sphere"))
	{
		parser->cur += ft_strlen("sphere");
        return (cmd_add_sphere(parser));
	}
//	 else if (ft_str_next_is(str, "plane"))
//		{
//		parser->cur += ft_strlen("plane");
//		return (cmd_add_plane(parser));
//	}
	// else if (ft_str_next_is(str, "cylinder"))
	// {
	// 	parser->cur += ft_strlen("cylinder");
    //     return (cmd_add_cylinder(parser));
	// }
	// else if (ft_str_next_is(str, "cone"))
	// {
	// 	parser->cur += ft_strlen("cone");
    //     return (cmd_add_cone(parser));
	// }
	return (msg_warn("Syntax error: Unknown object type"));
}
