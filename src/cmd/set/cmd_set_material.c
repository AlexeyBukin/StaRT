//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

int 				cmd_set_material_default(t_rt *rt, t_parser *parser)
{
	(void)rt;
	if (parser == NULL)
		return (rt_err("cmd_set_camera_default(): was given a NULL pointer"));
	return (0);
}

// 1) `-m` - metalness. Should be valid vector
// 2) `-r` - roughness. Should be be valid vector
// 3) `-i` - ior. Should be valid scalar
// 3) `-t` - transparency. Should be valid scalar
// 3) `-a` - albedo. Should be valid vector (values clamped 0..1)
// 3) `-f` - f0. Should be valid vector (values clamped 0..1)

t_msg				cmd_set_material_flags(t_mat *origin, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material_flags"))
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_material_flags: bad spaces"));
		if (cmd_read_material(parser))
			return (msg_warn("cmd_set_material_flags: bad syntax"));
	}
	ft_memcpy(origin, parser->material, sizeof(t_mat));
	return (msg_oks("material set success"));
}

t_msg				cmd_set_material(t_rt *rt, t_parser *parser)
{
	t_mat			*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_err("NULL pointer in cmd_set_material"));
	parser->cur += ft_strlen("material");
	if (cmd_read_space_req(&parser->cur))
		return(msg_warn("bad syntax: no space after material"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_set_material: bad name"));
	if ((tmp = scn_get_mat_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("no material with this name found"));
	parser->material = ft_memalloc(sizeof(t_mat));
	ft_memcpy(parser->material, tmp, sizeof(t_mat));
	return (cmd_set_material_flags(tmp, parser));
}
