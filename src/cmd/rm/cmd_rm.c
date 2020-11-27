#include "rt.h"

t_msg				cmd_rm_group_force(t_rt *rt, t_obj *group, int rm_force)
{
	if (group->type == OBJ_GROUP)
	{
		if (!rm_force)
			return (msg_warn("cmd_rm(): object with given name is a group."
							 " If you are sure you want to delete it, use flag -r."));
		if (scn_remove_by_name_grp(rt->scene, group->name))
			return (msg_warn("cmd_rm_group_force(): delete error"));
		return (msg_oks("cmd_rm(): removed object successfully"));
	}
	return (msg_warn("unknown object type"));
}

t_msg				cmd_rm_obj(t_rt *rt, t_parser *parser, int rm_force)
{
	t_obj		*tmp;
	int 	rm_err;

	rm_err = 0;
	if (rt == NULL || parser == NULL)
		return (msg_warn("cmd_rm_obj(): given NULL pointer"));
	if ((tmp = scn_get_obj_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("cmd_rm_obj(): object with"
		" given name does not exists"));
	if (tmp->type == OBJ_GROUP)
		return (cmd_rm_group_force(rt, tmp, rm_force));
	if (tmp->type == OBJ_COPY)
		rm_err = scn_remove_by_name_obj(rt->scene, tmp->name);
	else if (tmp->type == OBJ_CONTAINER)
		rm_err = scn_remove_by_name_copy(rt->scene, tmp->name);
	else
		return (msg_warn("unknown object type"));
	if (rm_err)
		return (msg_warn("cmd_rm_name(): couldn\'t remove an object"));
	return (msg_oks("cmd_rm(): removed object successfully"));
}

t_msg				cmd_rm_name(t_rt *rt, t_parser *parser, int rm_force)
{
	int 	rm_err;

	rm_err = 0;
	if (rt == NULL || parser == NULL)
		rm_err = (rt_err("NULL ptr in cmd_rm_name"));
	if (scn_get_cam_by_name(rt->scene, parser->name))
		rm_err = (scn_remove_by_name_cam(rt->scene, parser->name));
	if (scn_get_mat_by_name(rt->scene, parser->name))
		rm_err = (scn_remove_by_name_mat(rt->scene, parser->name));
	if (scn_get_txr_by_name(rt->scene, parser->name))
		rm_err = (scn_remove_by_name_txr(rt->scene, parser->name));
	if (rm_err)
		return (msg_warn("cmd_rm_name(): couldn\'t remove an object"));
	return (cmd_rm_obj(rt, parser, rm_force));
}

int				cmd_rm_force(t_parser *parser, int *rm_force)
{
	char		*str;

	str = parser->cur;
	cmd_read_space(&str);
	if (ft_str_next_is(str, "-r"))
	{
		str += ft_strlen("-r");
		*rm_force = 1;
		parser->cur = str;
	}
	return (0);
}

t_msg           cmd_rm(t_rt *rt, t_parser *parser)
{
	int		rm_force;

	rm_force = 0;
	if (rt == NULL || parser == NULL)
		return (msg_err("NULL ptr in cmd_rm"));
	cmd_rm_force(parser, &rm_force);
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("bad syntax"));
	if (cmd_read_string(&parser->cur, &parser->name))
		return (msg_warn("bad name string"));
	cmd_rm_force(parser, &rm_force);
	cmd_read_space(&parser->cur);
	if (*parser->cur)
		return (msg_err("cmd_rm(): bad syntax"));
	return (cmd_rm_name(rt, parser, rm_force));
}
