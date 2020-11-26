#include "rt.h"

int				cmd_rm_obj(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp;

	if (rt == NULL || parser == NULL)
		return (-1);
	if ((tmp = scn_get_obj_by_name(rt->scene, parser->name)) == NULL)
		return (-1);//scn_remove_by_name_obj
	if (tmp->type == OBJ_COPY)
		return (scn_remove_by_name_obj(rt->scene, tmp->name));//scn_remove_by_name_obj
	if (tmp->type == OBJ_CONTAINER)
		return (scn_remove_by_name_copy(rt->scene, tmp->name));//scn_remove_by_name_obj
	if (tmp->type == OBJ_GROUP)
	{
		if (ft_str_next_is("-r", parser->cur))
			return (scn_remove_by_name_grp(rt->scene, tmp->name));
	}
	return (0);
}

int				cmd_rm_name(t_rt *rt, t_parser *parser)
{
	if (rt == NULL || parser == NULL)
        return (rt_err("NULL ptr in cmd_rm_name"));
	if (scn_get_cam_by_name(rt->scene, parser->name))
		return (scn_remove_by_name_cam(rt->scene, parser->name));
	if (scn_get_mat_by_name(rt->scene, parser->name))
		return (scn_remove_by_name_mat(rt->scene, parser->name));
	if (scn_get_txr_by_name(rt->scene, parser->name))
		return (scn_remove_by_name_txr(rt->scene, parser->name));
	return (cmd_rm_obj(rt, parser));
}

t_msg           cmd_rm(t_rt *rt, t_parser *parser)
{
    if (rt == NULL || parser == NULL)
        return (msg_err("NULL ptr in cmd_rm"));
    if (cmd_read_space_req(&parser->cur))
        return (msg_warn("bad syntax"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (msg_warn("bad name string"));
	cmd_read_space(&parser->cur);
	if (cmd_rm_name(rt, parser))
		return (msg_warn("not any name match"));
	cmd_read_space(&parser->cur);
	if (ft_str_next_is(parser->cur, "-r"))
		parser->cur += ft_strlen("-r");
	if (*parser->cur)
		return (msg_warn("cmd_rm(): bad syntax"));
	return (msg_oks("remove success"));
}
