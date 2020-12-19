/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_vfx_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by hchau             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**		vfx sum "nonexistence_target" "mytxr1" "mytxr2"
**		vfx sum -f "existence_target" "mytxr1" "mytxr2"
*/

int			vfx_add_txr_to_scn(t_rt *rt, t_parser *parser)
{
	t_txr		*tmp;

	if ((tmp = scn_get_txr_by_name(rt->scene, parser->name)))
	{
		ft_free(tmp->content);
		if (tmp->filename)
			ft_free(tmp->filename);
		ft_free(tmp->name);
		ft_memcpy(tmp, parser->texture, sizeof(t_txr));
		ft_free(parser->texture);
		ft_free(parser->name);
	}
	else
	{
		ft_free(parser->name);
		if (scn_add_txr(rt->scene, parser->texture))
		{
			txr_deinit(parser->texture);
			return (rt_err("vfx_add_txr_to_scn(): "
			"can\'t add texture to scene"));
		}
	}
	return (0);
}

t_msg		cmd_vfx_sum(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_vfx_sum(): fatal: given NULL pointer"));
	if (cmd_vfx_sum_dest(rt, parser))
	{
		ft_free(parser->name);
		return (msg_warn("cmd_vfx_sum(): can\'t get dest texture"));
	}
	cmd_read_space(&parser->cur);
	if (ft_str_next_is(parser->cur, "sum"))
	{
		parser->cur += ft_strlen("sum");
		return (cmd_vfx_sum_read(rt, parser));
	}
	ft_free(parser->name);
	txr_deinit(parser->texture);
	return (msg_warn("cmd_vfx_sum(): unknown keyword"));
}
