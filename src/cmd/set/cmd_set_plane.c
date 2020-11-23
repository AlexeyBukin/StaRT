//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static t_msg		plane_parse_flags(t_parser *parser)
{
	if ((cmd_read_transform_part(parser)) < 0)
		return (msg_err("cmd_set_plane(): bad syntax in transform"));
	return (msg_oks("oks"));
}

void				cmd_set_plane_default(t_parser *parser)
{
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->container->shape.plane.radius = 0.0;
}

t_msg				cmd_set_plane(t_parser *parser)
{
	cmd_set_plane_default(parser);
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_err("cmd_set_plane(): bad syntax1"));
		plane_parse_flags(parser);
	}
	return (msg_oks("it works!"));
}
