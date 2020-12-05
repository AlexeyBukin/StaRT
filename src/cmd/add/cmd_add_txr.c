
#include "rt.h"

t_msg		cmd_add_txr_error(t_parser *parser, char *message)
{
	txr_deinit(parser->texture);
	return (msg_warn(message));
}

t_msg		cmd_read_txr(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax"));
		if (cmd_read_txr_type(parser))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax type"));
		if (cmd_read_txr_filename(parser))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax filename"));
	}
	if (cmd_add_txr_to_scn(rt, parser))
		return (cmd_add_txr_error(parser, "cmd_read_txr(): can\'t add texture to scene"));
	return (msg_oks("cmd_add_txr(): success"));
}

int			init_txr_parser(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	txr_init(&parser->texture, parser->name, (t_size2){1, 1});
	parser->texture->filename = NULL;
	return (0);
}

t_msg		cmd_add_txr(t_rt *rt, t_parser *parser)
{
	parser->cur += ft_strlen("texture");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_cone(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_cone(): bad name"));
	if (init_txr_parser(rt, parser))
		return (msg_err("cmd_add_cone(): critical malloc error"));
	return (cmd_read_txr(rt, parser));
}
