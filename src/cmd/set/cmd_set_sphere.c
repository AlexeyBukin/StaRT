//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static int			sphere_set_radius(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.sphere.radius))
			return (-1);
		return (1);
	}
	return (0);
}

static t_msg		sphere_parse_flags(t_parser *parser)
{
	int		parsed_args;

	parsed_args = 0;
	if ((parsed_args | (cmd_read_transform_part(parser))) < 0)
		return (msg_err("sphere_parse_flags(): bad syntax in transform"));
	if ((parsed_args | sphere_set_radius(parser)) < 0)
		return (msg_err("sphere_parse_flags(): bad syntax in rad"));
	if ((parsed_args | cmd_set_obj_attributes(parser)) < 0)
		return (msg_err("sphere_parse_flags(): bad syntax in attributes"));
	if (parsed_args < 1)
		return (msg_err("sphere_parse_flags(): bad syntax"));
	return (msg_oks("oks"));
}

void				cmd_set_sphere_default(t_parser *parser)
{
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->container->shape.sphere.radius = 0.0;
}

t_msg				cmd_set_sphere(t_parser *parser)
{
	cmd_set_sphere_default(parser);
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_err("cmd_set_sphere(): bad syntax1"));
		sphere_parse_flags(parser);
	}
	return (msg_oks("it works!"));
}
