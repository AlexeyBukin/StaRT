/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:41:35 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 21:55:10 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// -p - pos
// -a - angle

t_msg			init_sphere_parser(t_parser *parser)
{
	if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
		return (msg_err("Criticall err malloc"));
	parser->transform = &parser->object->transform;
	parser->container = &parser->object->content.container;
	parser->object->content.container.shape_type = SHP_SPHERE;
	return (msg_oks("ok"));
}

t_msg           cmd_add_sphere(t_parser *parser)
{
	if (parser == NULL)
		return(msg_err("cmd_add_sphere(): given NULL pointer in cmd_add()"));
    if (cmd_read_space_req(&parser->cur))
        return (msg_err("cmd_add_sphere(): bad syntax"));
    if (cmd_read_string(&(parser->cur), &(parser->name)))
        return (msg_err("cmd_add_sphere(): bad name"));
    init_sphere_parser(parser);
	return (cmd_set_sphere(parser));
}
