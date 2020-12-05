
#include "rt.h"

int		cmd_add_txr_to_scn(t_rt *rt, t_parser *parser)
{
	if (parser->texture->filename)
	{
		if (cmd_read_png(parser))
			return (rt_err("png read error"));
	}
	if (scn_add_txr(rt->scene, parser->texture))
		return (rt_err("cmd_add_txr_to_scn(): name collision"));
	return (0);
}
