//
// Created by Hugor Chau on 11/29/20.
//

#include "rt.h"

t_msg		cmd_render(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	parser->cur += ft_strlen("render");
	return (msg_warn("TODO: add render"));
}