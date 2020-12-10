/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg				cmd_rm_error(t_parser *parser, char *message)
{
	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg				cmd_set_error(t_parser *parser, char *message)
{
	ft_free(parser->object->name);
	ft_free(parser->object);
	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg				cmd_add_error(t_parser *parser, char *error_message)
{
	obj_deinit(parser->object);
	return (msg_warn(error_message));
}
