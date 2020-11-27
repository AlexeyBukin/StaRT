//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

int 				cmd_set_material_default(t_rt *rt, t_parser *parser)
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

// 1) `-m` - metalness. Should be valid vector
// 2) `-r` - roughness. Should be be valid vector
// 3) `-i` - ior. Should be valid scalar
// 3) `-t` - transparency. Should be valid scalar
// 3) `-a` - albedo. Should be valid vector (values clamped 0..1)
// 3) `-f` - f0. Should be valid vector (values clamped 0..1)

t_msg				cmd_set_material_flags(t_mat *dest, t_parser *parser)
{
	if (dest == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material_flags"));
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_material_flags: bad spaces"));
		if (cmd_read_material(parser))
			return (msg_warn("cmd_set_material_flags: bad syntax"));
	}
	ft_memcpy(dest, parser->material, sizeof(t_mat));
	return (msg_oks("material set success"));
}

static int			init_material_parser(t_parser *parser, t_mat *src)
{
	parser->material = ft_memalloc(sizeof(t_mat));
	ft_memcpy(parser->material, src, sizeof(t_mat));
	return (0);
}

t_msg				cmd_set_material(t_rt *rt, t_parser *parser)
{
	t_mat			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material"));
	if ((tmp = scn_get_mat_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("no material with this name found"));
	if (init_material_parser(parser, tmp))
		return (msg_err("cmd_set_material(): critical malloc error"));
	return (cmd_set_material_flags(tmp, parser));
}
