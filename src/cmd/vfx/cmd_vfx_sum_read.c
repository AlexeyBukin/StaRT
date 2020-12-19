/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_vfx_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by hchau             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_txr_lst(t_list *txrs)
{
	t_list		*tmp;

	while (txrs)
	{
		tmp = txrs->next;
		ft_free(txrs->content);
		ft_free(txrs);
		txrs = tmp;
	}
}

t_msg		cmd_vfx_error(t_parser *parser, t_list *txrs, char *message)
{
	free_txr_lst(txrs);
	if (parser->texture)
		txr_deinit(parser->texture);
	ft_free(parser->name);
	return (msg_warn(message));
}

int			cmd_vfx_read_name(t_rt *rt, t_parser *parser, t_list **txr)
{
	t_txr		*res;
	char		*name;
	t_list		*tmp;

	if (rt == NULL || parser == NULL || txr == NULL)
		return (rt_err("cmd_vfx_read_name(): fatal: given NULL pointer"));
	if (*parser->cur == '\"')
	{
		if (cmd_read_string(&parser->cur, &name))
		{
			return (rt_err("cmd_vfx_read_name(): "
			"name parsing err"));
		}
		if ((res = scn_get_txr_by_name(rt->scene, name)) == NULL)
		{
			ft_free(name);
			return (rt_err("cmd_vfx_read_name(): no texture with given name"));
		}
		ft_free(name);
		if ((tmp = ft_lstnew(&res, sizeof(t_txr **))) == NULL)
			return (rt_err("cmd_vfx_read_name(): fatal malloc error"));
		ft_lstadd(txr, tmp);
	}
	return (0);
}

t_msg		cmd_vfx_sum_read(t_rt *rt, t_parser *parser)
{
	t_list		*txrs;

	txrs = NULL;
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_vfx_read(): fatal: given NULL pointer"));
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_vfx_error(parser, txrs, "cmd_vfx_read(): "
			"bad syntax or unknown flag"));
		if (cmd_vfx_read_name(rt, parser, &txrs))
			return (cmd_vfx_error(parser, txrs, "cmd_vfx_sum(): bad syntax"));
	}
	if (txr_sum_lst(txrs, parser->texture))
		return (cmd_vfx_error(parser, txrs, "cmd_vfx_sum(): sum is not ok"));
	free_txr_lst(txrs);
	if (vfx_add_txr_to_scn(rt, parser))
		return (msg_warn("cmd_vfx_sum(): can\'t add texture to scene"));
	return (msg_oks("cmd_vfx_sum(): success"));
}
