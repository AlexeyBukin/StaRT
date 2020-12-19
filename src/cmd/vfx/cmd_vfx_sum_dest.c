/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_vfx_sum_dest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by hchau             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			copy_txr(t_parser *parser, t_txr *src)
{
	if (txr_init_default(&parser->texture, ft_strdup(parser->name)))
		return (rt_err("cmd_vfx_dest(): fatal: malloc error"));
	if (src->filename)
	{
		parser->texture->filename = ft_strdup(src->filename);
		if (parser->texture->filename == NULL)
		{
			txr_deinit(parser->texture);
			return (rt_err("copy_txr(): fatal: malloc error"));
		}
	}
	parser->texture->type = src->type;
	parser->texture->width = src->width;
	parser->texture->height = src->height;
	parser->texture->stride = src->stride;
	if (parser->texture->width != 0 && parser->texture->height != 0)
		parser->texture->content = ft_memalloc(sizeof(char)
			* src->stride * src->height);
	ft_memcpy(parser->texture->content, src->content,
			sizeof(char) * (src->stride * src->height));
	return (0);
}

int			cmd_vfx_sum_dest_force(t_rt *rt, t_parser *parser)
{
	t_txr	*tmp;

	if (rt == NULL || parser == NULL)
		return (rt_err("cmd_vfx_dest(): fatal: given NULL pointer"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (rt_err("cmd_vfx_dest(): bad name"));
	if ((tmp = scn_get_txr_by_name(rt->scene, parser->name)) != NULL)
	{
		if (copy_txr(parser, tmp))
			return (rt_err("cmd_vfx_sum_dest_force(): copy error"));
		return (0);
	}
	if (txr_init_default(&parser->texture, ft_strdup(parser->name)))
		return (rt_err("cmd_vfx_dest(): fatal: malloc error"));
	return (0);
}

int			cmd_vfx_sum_dest_new(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (rt_err("cmd_vfx_dest(): fatal: given NULL pointer"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (rt_err("cmd_vfx_dest(): bad name"));
	if (scn_get_txr_by_name(rt->scene, parser->name))
		return (rt_err("cmd_vfx_dest(): can\'t modify "
		"texture without -f flag"));
	if (txr_init_default(&parser->texture, ft_strdup(parser->name)))
		return (rt_err("cmd_vfx_dest(): fatal: malloc error"));
	return (0);
}

int			cmd_vfx_sum_dest(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (rt_err("cmd_vfx_dest(): fatal: given NULL pointer"));
	cmd_read_space(&parser->cur);
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		return (cmd_vfx_sum_dest_force(rt, parser));
	}
	return (cmd_vfx_sum_dest_new(rt, parser));
}
