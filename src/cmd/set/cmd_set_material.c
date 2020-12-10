/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**  `-m` - metalness. Should be valid vector
**  `-r` - roughness. Should be be valid vector
**  `-i` - ior. Should be valid scalar
**  `-t` - transparency. Should be valid scalar
**  `-a` - albedo. Should be valid vector (values clamped 0..1)
**  `-f` - f0. Should be valid vector (values clamped 0..1)
*/

static t_msg		set_material_error(t_parser *parser, char *message)
{
	mat_deinit(parser->material);
	return (msg_warn(message));
}

int					cmd_set_material_default(t_rt *rt, t_parser *parser)
{
	(void)rt;
	if (parser == NULL)
		return (rt_err("cmd_set_camera_default(): was given a NULL pointer"));
	parser->material->content.pbr.metalness = 0.0;
	parser->material->content.pbr.roughness = 0.5;
	parser->material->content.pbr.ior = 1.2;
	parser->material->content.pbr.transparency = 0.0;
	parser->material->content.pbr.albedo = vec3(0.5, 0.5, 0.5);
	parser->material->content.pbr.f0 = vec3(0.05, 0.05, 0.05);
	return (0);
}

t_msg				cmd_set_material_flags(t_rt *rt,
					t_mat *dest, t_parser *parser)
{
	if (dest == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material_flags"));
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (set_material_error(parser, ""
			"cmd_set_material_flags: bad spaces"));
		if (cmd_read_material(parser))
			return (set_material_error(parser, ""
			"cmd_set_material_flags: bad syntax"));
		if (cmd_set_obj_name(rt, parser))
			return (set_material_error(parser, ""
			"cmd_set_material_flags: bad name"));
	}
	return (cmd_set_mat_to_scn(parser, dest));
}

static int			init_material_parser(t_parser *parser, t_mat *src)
{
	mat_init(&parser->material, parser->name);
	ft_memcpy(parser->material, src, sizeof(t_mat));
	parser->material->name = ft_strdup(parser->name);
	return (0);
}

t_msg				cmd_set_material(t_rt *rt, t_parser *parser)
{
	t_mat			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material"));
	if ((tmp = scn_get_mat_by_name(rt->scene, parser->name)) == NULL)
	{
		ft_free(parser->name);
		return (msg_warn("no material with this name found"));
	}
	if (init_material_parser(parser, tmp))
	{
		ft_free(parser->name);
		return (msg_err("cmd_set_material(): critical malloc error"));
	}
	return (cmd_set_material_flags(rt, tmp, parser));
}
