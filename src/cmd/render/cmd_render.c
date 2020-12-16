/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO debug, png-filename
#include "rt.h"

int			cmd_render_check(t_parser *parser, t_size2 *w_h, t_size2 *tile)
{
	if (parser->name == NULL)
		return (rt_err("cmd_render(): filename is missing"));
	if (tile->x == 0 && tile->y == 0)
		*tile = *w_h;
	return (0);
}

t_msg		cmd_end_render(t_rt *rt, char *filename, t_size2 tile, int tile_num)
{
	if (cmd_on_render(rt, filename, tile, tile_num))
	{
		free(filename);
		return (msg_warn("cmd_end_render(): cmd_on_render() error"));
	}
	free(filename);
	return (msg_oks("cmd_render(): success"));
}

t_msg		cmd_render_read(t_rt *rt, t_parser *parser,
							 t_size2 tile, int tile_num)
{
	t_size2		w_h;

	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_render(): given NULL pointer"));
	w_h = (t_size2){0, 0};
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_error(parser, "cmd_render(): bad syntax"));
		if (cmd_render_read_tile_num(parser, &tile_num))
			return (cmd_add_error(parser, "cmd_render(): bad syntax -t"));
		if (cmd_render_read_height(parser, &w_h.y))
			return (cmd_add_error(parser, "cmd_render(): bad syntax -h"));
		if (cmd_render_read_width(parser, &w_h.x))
			return (cmd_add_error(parser, "cmd_render(): bad syntax -w"));
		if (cmd_render_read_square(parser, &tile))
			return (cmd_add_error(parser, "cmd_render(): bad syntax -s"));
		if (cmd_render_read_name(parser, &parser->name))
			return (cmd_add_error(parser, "cmd_render(): bad syntax filename"));
	}
	if (cmd_render_check(parser, &w_h, &tile))
		return (msg_warn("cmd_render(): parser error"));
	return (cmd_end_render(rt, parser->name, tile, tile_num));
}

t_msg		cmd_render(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_render(): given NULL pointer"));
	parser->cur += ft_strlen("render");
	parser->name = NULL;
	return (cmd_render_read(rt, parser, (t_size2){0, 0}, 0));
}
