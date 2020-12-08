/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			cmd_read_fov(t_parser *parser)
{
	if (parser == NULL)
		return (-1);
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		return (cmd_read_vec2(&(parser->cur),
		&(parser->object->content.camera.fov)));
	}
	return (0);
}

static t_msg		cmd_set_camera_flags(t_rt *rt,
							t_parser *parser, t_obj *dest)
{
	if (dest == NULL || parser == NULL)
		return (msg_err("NULL in cmd_set_cametra_flags"));
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax1"));
		if (cmd_read_transform_part(parser))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax in transform"));
		if (cmd_read_fov(parser))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax in fov"));
		if (cmd_set_obj_name(rt, parser))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax visibility"));
		if (cmd_set_obj_visibility(parser))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser))
			return (cmd_set_error(parser, ""
			"cmd_set_camera(): bad syntax group"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg				cmd_set_camera(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (parser == NULL || rt == NULL || dest == NULL)
		return (msg_err("cmd_set_camera(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_camera(): critical malloc error"));
	return (cmd_set_camera_flags(rt, parser, dest));
}
