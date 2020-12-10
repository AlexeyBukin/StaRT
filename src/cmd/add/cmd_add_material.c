/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	`-m` - metalness. Should be valid vector ????
**	`-r` - roughness. Should be be valid vector ????
**	`-i` - ior. Should be valid scalar
**	`-t` - transparency. Should be valid scalar
**	`-a` - albedo. Should be valid vector (values clamped 0..1)
**	`-f` - f0. Should be valid vector (values clamped 0..1)
*/

static int			init_material_parser(t_rt *rt, t_parser *parser)
{
	if (mat_init(&parser->material, parser->name))
		return (rt_err("Criticall err malloc"));
	if (cmd_set_material_default(rt, parser))
		return (rt_warn("Given a NULL pointer"));
	return (0);
}

static t_msg		add_material_error(t_parser *parser, char *message)
{
	ft_free(parser->material);
	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg				cmd_parse_material_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (add_material_error(parser, ""
			"cmd_parse_material_flags(): bad syntax1"));
		if (cmd_read_material(parser))
			return (add_material_error(parser, ""
			"cmd_parse_material_flags(): bad syntax1"));
	}
	if (scn_add_mat(rt->scene, parser->material))
		return (add_material_error(parser, "couldn\'t add material to scene"));
	return (msg_oks("material added successfully"));
}

t_msg				cmd_add_material(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_material(): given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("material");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_material(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_material(): bad name"));
	if (init_material_parser(rt, parser))
		return (msg_err("cmd_add_material(): critical malloc error"));
	return (cmd_parse_material_flags(rt, parser));
}
