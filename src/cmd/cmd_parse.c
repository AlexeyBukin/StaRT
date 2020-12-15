/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 21:47:47 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/

/*
** work with string as single command, so need to manage it in one move
** when we get word we try to:
** 1) find out is it command ( else unknown command quit)
** 1.1) extra funcs for each command for better err managment
** 2) find out is it arg (if args is invalid - quit err invalid args)
** 3) find out is it flags (ignore invalid flags)
** 4) check out values associated with flags is it valid
**		(if not - set default vals)
*/

t_msg					cmd_parse_line(t_rt *rt, char *source)
{
	t_msg				res;
	t_parser			*parser;

	if ((parser = ft_malloc(sizeof(t_parser))) == NULL)
		return (msg_err("Memory allocation error on cmd_parse_line"));
	parser->container = &parser->object->content.container;
	parser->transform = &parser->object->transform;
	parser->source = source;
	parser->cur = source;
	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	res = cmd_parse_command(rt, parser);
	ft_free(parser);
	return (res);
}
