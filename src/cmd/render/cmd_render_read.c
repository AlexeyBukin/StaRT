/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_render_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			cmd_render_read_name(t_parser *parser, char **filename)
{
	if (parser == NULL || filename == NULL)
		return (rt_err("cmd_render_read_name(): given NULL pointer"));
	if (*parser->cur == '\"')
	{
		if (*filename != NULL)
			ft_free(*filename);
		return (cmd_read_string(&parser->cur, filename));
	}
	return (0);
}

int			cmd_render_read_width(t_parser *parser, size_t *w)
{
	if (parser == NULL || w == NULL)
		return (rt_err("cmd_render_read_name(): given NULL pointer"));
	if (ft_str_next_is(parser->cur, "-w"))
	{
		parser->cur += ft_strlen("-w");
		cmd_read_space(&parser->cur);
		if (cmd_read_uint(&parser->cur, (uint *)w))
			return (rt_err("cmd_render_read_height(): num parsing error"));
	}
	return (0);
}

int			cmd_render_read_height(t_parser *parser, size_t *h)
{
	if (parser == NULL || h == NULL)
		return (rt_err("cmd_render_read_name(): given NULL pointer"));
	if (ft_str_next_is(parser->cur, "-h"))
	{
		parser->cur += ft_strlen("-h");
		cmd_read_space(&parser->cur);
		if (cmd_read_uint(&parser->cur, (uint *)h))
			return (rt_err("cmd_render_read_height(): num parsing error"));
	}
	return (0);
}

int			cmd_render_read_square(t_parser *parser, t_size2 *square)
{
	if (parser == NULL || square == NULL)
		return (rt_err("cmd_render_read_name(): given NULL pointer"));
	if (ft_str_next_is(parser->cur, "-s"))
	{
		parser->cur += ft_strlen("-s");
		cmd_read_space(&parser->cur);
		if (cmd_read_uint(&parser->cur, (uint *)&square->x))
			return (rt_err("cmd_render_read_height(): num parsing error"));
		square->y = square->x;
	}
	return (0);
}

int			cmd_render_read_tile_num(t_parser *parser, int *tile_num)
{
	if (parser == NULL || tile_num == NULL)
		return (rt_err("cmd_render_read_name(): given NULL pointer"));
	if (ft_str_next_is(parser->cur, "-t"))
	{
		parser->cur += ft_strlen("-t");
		cmd_read_space(&parser->cur);
		if (cmd_read_uint(&parser->cur, (uint *)tile_num))
			return (rt_err("cmd_render_read_height(): num parsing error"));
	}
	return (0);
}
