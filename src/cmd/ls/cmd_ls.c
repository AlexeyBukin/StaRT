/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_ls(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	parser->cur += ft_strlen("ls");
	if (scn_print(rt->scene))
		return (msg_warn("cmd_parse_command(): couldn\'t print objects"));
	return (msg_oks("It\'s for debug only"));
}
