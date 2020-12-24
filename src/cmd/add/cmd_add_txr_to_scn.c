/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_txr_to_scn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		cmd_read_txr_error(t_rt *rt, t_parser *parser)
{
	t_txr		*tmp;

	if (fio_png_read_name(&tmp, ft_strdup(parser->texture->filename),
			ft_strdup(parser->texture->name)))
		return (rt_err("png read error"));
	if (parser->texture->type == TXR_NONE)
		parser->texture->type = tmp->type;
	if (tmp->type != parser->texture->type)
	{
		txr_deinit(tmp);
		return (rt_err("add_txr_error(): png read error"));
	}
	if (scn_add_txr(rt->scene, tmp))
	{
		txr_deinit(tmp);
		return (rt_err("add_txr_error(): name collision"));
	}
	txr_deinit(parser->texture);
	return (0);
}

int				cmd_add_txr_to_scn(t_rt *rt, t_parser *parser)
{
	if (parser->texture->filename)
	{
		if (cmd_read_txr_error(rt, parser))
			return (rt_err("cmd_add_txr_to_scn(): error"));
		return (0);
	}
	parser->texture->type = TXR_RGB_8;
	if (scn_add_txr(rt->scene, parser->texture))
		return (rt_err("cmd_add_txr_to_scn(): name collision"));
	return (0);
}
