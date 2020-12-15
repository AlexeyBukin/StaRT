/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_txr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_msg		cmd_set_txr_error(t_parser *parser, char *message)
{
	ft_free(parser->texture);
	ft_free(parser->name);
	if (parser->texture->filename)
		ft_free(parser->texture->filename);
	return (msg_warn(message));
}

t_msg				cmd_set_read_txr(t_rt *rt, t_txr *dest, t_parser *parser)
{
	if (dest == NULL || parser == NULL || rt == NULL)
		return (msg_err("NULL pointer in cmd_set_read_txr()"));
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_txr_error(parser, ""
			"cmd_read_txr(): bad syntax"));
		if (cmd_read_txr_type(parser))
			return (cmd_set_txr_error(parser, ""
			"cmd_read_txr(): bad syntax type"));
		if (cmd_read_txr_filename(parser))
			return (cmd_set_txr_error(parser, ""
			"cmd_read_txr(): bad syntax filename"));
		if (cmd_set_obj_name(rt, parser))
			return (cmd_set_txr_error(parser, ""
			"cmd_read_txr(): bad syntax filename"));
	}
	return (cmd_set_txr_to_scn(parser, dest));
}

static int			init_txr_parser(t_parser *parser, t_txr *src)
{
	if ((parser->texture = ft_memalloc(sizeof(t_txr))) == NULL)
		return (rt_err("malloc error"));
	ft_memcpy(parser->texture, src, sizeof(t_txr));
	if (src->filename)
	{
		parser->texture->filename = ft_strdup(src->filename);
		if (parser->texture->filename == NULL)
			return (rt_err("malloc error"));
	}
	return (0);
}

t_msg				cmd_set_txr(t_rt *rt, t_parser *parser)
{
	t_txr			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_txr"));
	if ((tmp = scn_get_txr_by_name(rt->scene, parser->name)) == NULL)
	{
		ft_free(parser->name);
		return (msg_warn("no texture with this name found"));
	}
	if (init_txr_parser(parser, tmp))
	{
		ft_free(parser->name);
		return (msg_err("cmd_set_txr(): critical malloc error"));
	}
	return (cmd_set_read_txr(rt, tmp, parser));
}
