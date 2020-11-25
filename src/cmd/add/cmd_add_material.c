//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

/*
**	`-m` - metalness. Should be valid vector ????
**	`-r` - roughness. Should be be valid vector ????
**	`-i` - ior. Should be valid scalar
**	`-t` - transparency. Should be valid scalar
**	`-a` - albedo. Should be valid vector (values clamped 0..1)
**	`-f` - f0. Should be valid vector (values clamped 0..1)
*/

int 					cmd_read_material_limited_vecs(t_parser *parser)
{
	t_vec3			tmp;

	if (ft_str_next_is(parser->cur, "-a"))
	{
		parser->cur += ft_strlen("-a");
		cmd_read_space(&parser->cur);
		if (cmd_read_vec(&(parser->cur), &tmp))
			return (rt_err("couldn\'t parse vector"));
		if (tmp.x < 0 || tmp.x > 1.0
			|| tmp.y < 0 || tmp.y > 1.0
			|| tmp.z < 0 || tmp.z > 1.0)
			return (rt_err("cmd_read_material_limited_vecs(): "
				"albedo values should be clamped 0..1"));
		parser->material->content.pbr.albedo = tmp;
	}
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		if (cmd_read_vec(&(parser->cur), &tmp))
			return (rt_err("couldn\'t parse vector"));
		if (tmp.x < 0 || tmp.x > 1.0
			|| tmp.y < 0 || tmp.y > 1.0
			|| tmp.z < 0 || tmp.z > 1.0)
			return (rt_err("cmd_read_material_limited_vecs(): "
						   "f0 values should be clamped 0..1"));
		parser->material->content.pbr.f0 = tmp;

	}
	return (0);
}

int						cmd_read_material(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.metalness)));
	}
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.roughness)));
	}
	if (ft_str_next_is(parser->cur, "-i"))
	{
		parser->cur += ft_strlen("-i");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.ior)));
	}
	if (ft_str_next_is(parser->cur, "-t"))
	{
		parser->cur += ft_strlen("-t");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.transparency)));
	}
	return (cmd_read_material_limited_vecs(parser));
}

static t_msg			init_material_parser(t_rt *rt, t_parser *parser)
{
	if (mat_init(&parser->material, parser->name))
		return (msg_err("Criticall err malloc"));
	if (cmd_set_material_default(rt, parser))
		return (msg_warn("Given a NULL pointer"));
	return (msg_oks("ok"));
}

t_msg				cmd_parse_material_flags(t_rt *rt, t_parser *parser)
{
	(void)rt;
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_parse_material_flags(): bad syntax1"));
		if (cmd_read_material(parser))
			return (msg_warn("cmd_parse_material_flags(): bad syntax1"));
	}
	scn_add_mat(rt->scene, parser->material);
	return (msg_oks("it works!"));
}

t_msg				cmd_add_material(t_rt *rt, t_parser *parser)
{
	if (parser == NULL)
		return(msg_err("cmd_add_material(): given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_material(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_material(): bad name"));
	init_material_parser(rt, parser);
	return (cmd_parse_material_flags(rt, parser));
}