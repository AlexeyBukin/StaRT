/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_vfx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by hchau             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg		cmd_vfx(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_vfx(): fatal: given NULL pointer"));
	parser->cur += ft_strlen("vfx");
	parser->texture = NULL;
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_vfx(): bad syntax"));
	return (cmd_vfx_sum(rt, parser));
}
