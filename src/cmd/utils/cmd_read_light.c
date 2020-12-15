/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		cmd_light_set_intensity(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-i"))
	{
		parser->cur += ft_strlen("-i");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur,
			&parser->object->content.light.light.intensity))
			return (-1);
		return (0);
	}
	return (0);
}

int		cmd_light_set_type(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-l"))
	{
		parser->cur += ft_strlen("-l");
		cmd_read_space(&parser->cur);
		if (ft_str_next_is(parser->cur, "point"))
		{
			parser->cur += ft_strlen("point");
			parser->object->content.light.lgt_type = LGT_POINT;
			return (0);
		}
		if (ft_str_next_is(parser->cur, "parallel"))
		{
			parser->cur += ft_strlen("parallel");
			parser->object->content.light.lgt_type = LGT_PARALLEL;
			return (0);
		}
		return (-1);
	}
	return (0);
}

int		cmd_light_set_color(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-c"))
	{
		parser->cur += ft_strlen("-c");
		cmd_read_space(&parser->cur);
		if (cmd_read_vec(&parser->cur,
			&parser->object->content.light.light.color))
			return (-1);
	}
	return (0);
}
