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

int		cmd_add_txr_to_scn(t_rt *rt, t_parser *parser)
{
	if (parser->texture->filename)
	{
		if (fio_read_png(parser->texture))
			return (rt_err("png read error"));
	}
	if (scn_add_txr(rt->scene, parser->texture))
		return (rt_err("cmd_add_txr_to_scn(): name collision"));
	return (0);
}
