/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:52:44 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 19:52:24 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			cmd_pos(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
	return (cmd_read_vec(&parser->cur, &parser->transform->pos_local));
}

int			cmd_rot(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
	return (cmd_read_vec(&parser->cur, &parser->rot_euler_xyz));
}

int			cmd_read_transform_part(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
    if (ft_str_next_is(parser->cur, "-p"))
    {
        parser->cur += ft_strlen("-p");
        if (cmd_pos(parser))
			return (-1);
    }
	else if (ft_str_next_is(parser->cur, "-a"))
	{
        parser->cur += ft_strlen("-a");
        if (cmd_rot(parser))
			return (-1);
    }
	return (0);
}
