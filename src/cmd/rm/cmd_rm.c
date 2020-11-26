#include "rt.h"

int				cmd_rm_recur(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
        return (msg_err("NULL ptr in cmd_rm_name"));
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (-1);
		
	}

}

int				cmd_rm_name(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
        return (msg_err("NULL ptr in cmd_rm_name"));
	if (ft_str_next_is(parser->cur, "-n"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (-1);
		if (cmd_read_string(&parser->cur, &parser->name))
			return (-1);
		if (scn_get_cam_by_name(rt->scene, parser->name))
			return (scn_remove_by_name_cam(rt->scene, parser->name));
		if (scn_get_mat_by_name(rt->scene, parser->name))
			return (scn_remove_by_name_mat(rt->scene, parser->name));;
		if (scn_get_txr_by_name(rt->scene, parser->name))
			return (scn_remove_by_name_txr(rt->scene, parser->name));;
		if (scn_get_obj_by_name(rt->scene, parser->name))
			;//scn_remove_by_name_obj
		else
			return(-1);
	}
	return (0);
}

t_msg           cmd_rm(t_rt *rt, t_parser *parser)
{
    if (rt == NULL || parser == NULL)
        return (msg_err("NULL ptr in cmd_rm"));
    if (cmd_read_space_req(&parser->cur))
        return (msg_warn("bad syntax"));
    
    if (scn_get_obj_by_name(rt->scene, parser->name))
}
