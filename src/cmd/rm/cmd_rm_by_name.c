#include "rt.h"

t_msg				safe_rm(int error)
{
	if (error)
		return (msg_warn("cmd_rm_name(): couldn\'t remove an object"));
	return (msg_oks("cmd_rm(): removed object successfully"));
}

t_msg				cmd_rm_group_force(t_rt *rt, t_obj *group, int rm_force)
{
	if (group->type == OBJ_GROUP)
	{
		if (!rm_force)
			return (msg_warn("cmd_rm(): object with given name is a group."
							 " If you are sure you want to delete it, use flag -r."));
		if (group->parent == NULL)
			return (msg_warn("cmd_rm(): can\'t remove main group."));
		return (safe_rm(scn_remove_by_name_grp(rt->scene, group->name)));
	}
	return (msg_warn("unknown object type"));
}

t_msg				cmd_rm_obj(t_rt *rt, t_parser *parser, int rm_force)
{
	t_obj		*tmp;

	if (rt == NULL || parser == NULL)
		return (msg_warn("cmd_rm_obj(): given NULL pointer"));
	if ((tmp = scn_get_obj_by_name(rt->scene, parser->name)) == NULL)
		return (msg_warn("cmd_rm_obj(): object with"
						 " given name does not exists"));
	if (tmp->type == OBJ_GROUP)
		return (cmd_rm_group_force(rt, tmp, rm_force));
	if (tmp->type == OBJ_COPY)
		return safe_rm(scn_remove_by_name_obj(rt->scene, tmp->name));
	else if (tmp->type == OBJ_CONTAINER)
		return (safe_rm(scn_remove_by_name_copy(rt->scene, tmp->name)));
	return (msg_warn("cmd_rm_name(): couldn\'t remove an object"));
}

t_msg				cmd_rm_by_name(t_rt *rt, t_parser *parser, int rm_force)
{
	if (rt == NULL || parser == NULL)
		return (msg_warn("NULL ptr in cmd_rm_name"));
	if (scn_get_cam_by_name(rt->scene, parser->name))
		return (safe_rm(scn_remove_by_name_cam(rt->scene, parser->name)));
	if (scn_get_mat_by_name(rt->scene, parser->name))
	{
		if (cmd_rm_material(rt, parser))
			return (msg_warn("cmd_rm_by_name(): couldn't remove material"));
		return (safe_rm(scn_remove_by_name_mat(rt->scene, parser->name)));
	}
	if (scn_get_txr_by_name(rt->scene, parser->name))
		return (safe_rm(scn_remove_by_name_txr(rt->scene, parser->name)));
	return (cmd_rm_obj(rt, parser, rm_force));
}
