//
// Created by Hugor Chau on 11/30/20.
//
#include "rt.h"

t_msg				cmd_rm_error(t_parser *parser, char *message)
{
	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg				cmd_set_error(t_parser *parser, char *message)
{
	obj_deinit(parser->object);
	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg				cmd_add_error(t_parser *parser, char *error_message)
{
	obj_deinit(parser->object);
	return (msg_warn(error_message));
}
