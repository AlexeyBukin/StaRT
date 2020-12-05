
#include "rt.h"

static int		recognise_txr_type(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "RGB8"))
	{
		parser->cur += ft_strlen("RGB8");
		parser->texture->type = TXR_RGB_8;
		return (0);
	}
	if (ft_str_next_is(parser->cur, "RGBA8"))
	{
		parser->cur += ft_strlen("RGBA8");
		parser->texture->type = TXR_RGBA_8;
		return (0);
	}
	if (ft_str_next_is(parser->cur, "BW8"))
	{
		parser->cur += ft_strlen("BW8");
		parser->texture->type = TXR_BW_8;
		return (0);
	}
	return (-1);
}

int			cmd_read_txr_type(t_parser *parser)
{
	if (parser == NULL || parser->name == NULL)
		return (rt_err("cmd_read_txr_type(): given NULL pointer"));
	if (ft_str_next_is(parser->cur, "-t"))
	{
		parser->cur += ft_strlen("-t");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_read_txr_type(): bad syntax"));
		return (recognise_txr_type(parser));
	}
	return (0);
}

int			cmd_read_txr_filename(t_parser *parser)
{
	char	*name;

	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_read_txr(): bad syntax"));
		if (cmd_read_string(&parser->cur, &name))
			return (-1);
		if (parser->texture->filename)
			ft_free(parser->texture->filename);
		parser->texture->filename = name;
		return (0);
	}
	return (0);
}
