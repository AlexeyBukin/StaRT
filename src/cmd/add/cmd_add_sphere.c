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

t_msg           cmd_add_sphere(t_parser *parser)
{
	int			val;

    if (parser == NULL)
		return(msg_err("Given NULL pointer in cmd_add()"));
    if (cmd_read_space_req(&parser->cur))
        return (msg_err("Bad syntax"));
    if (cmd_read_string(&parser->cur, &parser->name))
        return (msg_err("Bad name"));
    if (obj_init(&parser->object, parser->name, OBJ_CONTAINER))
        return (msg_err("Criticall err malloc"));
    ft_printf("read sphere ready!");
    while (*parser->cur != '\0' && *parser->cur != '\n')
    {
		if (cmd_read_space_req(&parser->cur))
        	return (msg_err("Bad syntax"));
		if ((val = cmd_read_transform_part(parser)) < 0)
			return (msg_err("Bad syntax"));
		if (val != 0)
			continue ;
        // if (ft_str_next_is(parser->cur, "-r"))
        // {
        //     parser->cur += ft_strlen("-r");
        //     if (cmd_read_num(&parser->cur, &parser->container->shape.sphere.radius))
		// 		return (msg_err("Bad syntax"));
        // }
        // else
            return (msg_err("Bad syntax"));
    }
    ft_printf("read sphere success!");
	return (msg_oks("Sphere read success!"));
}

// parser->cont = &pareser->object.content.container;
// parser->transform = &pareser->object.transform;
	