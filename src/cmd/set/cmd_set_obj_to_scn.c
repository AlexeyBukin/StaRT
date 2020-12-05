
#include "rt.h"

t_msg			cmd_set_txr_to_scn(t_parser *parser, t_txr *dest)
{
	if (dest->filename &&
		!(ft_strequ(parser->texture->filename,
			dest->filename)))
	{
		if (cmd_read_png(parser))
		{
			//TODO leaks!!!
			return (msg_warn("png read error"));
		}
		ft_free(dest->content);
		ft_free(dest->filename);
	}
	ft_free(dest->name);
	ft_memcpy(dest, parser->texture, sizeof(t_txr));
	dest->name = ft_strdup(parser->name);
	ft_free(parser->name);
	ft_free(parser->texture);
	return (msg_oks("set txr success"));
}

t_msg			cmd_set_mat_to_scn(t_parser *parser, t_mat *dest)
{
	ft_free(dest->name);
	ft_memcpy(dest, parser->material, sizeof(t_mat));
	dest->name = ft_strdup(parser->name);
	mat_deinit(parser->material);
	ft_free(parser->name);
	return (msg_oks("material set success"));
}

int			cmd_move_obj(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (parser->group != dest->parent && parser->group != NULL)
	{
		if (scn_move_obj(rt->scene, parser->group, dest))
			return (rt_err("can\'t change object group"));
	}
	return (0);
}

t_msg			cmd_set_obj_to_scn(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL || dest == NULL)
		return (msg_err("cmd_set_obj_to_scn(): given NULL pointer"));
	if (cmd_move_obj(rt, parser, dest))
		return (cmd_set_error(parser, "can\'t change object group"));
	ft_free(dest->name);
	ft_memcpy(dest, parser->object, sizeof(t_obj));
	dest->name = ft_strdup(parser->name);
	dest->parent = parser->group;
	dest->transform.rot_local.x = vec3_normalize(dest->transform.rot_local.x);
	dest->transform.rot_local.y = vec3_normalize(dest->transform.rot_local.y);
	dest->transform.rot_local.z = vec3_normalize(dest->transform.rot_local.z);
	if (dest->type == OBJ_CONTAINER || dest->type == OBJ_COPY)
	{
		dest->content.container.material = parser->material;
	}
	ft_free(parser->object->name);
	ft_free(parser->object);
	ft_free(parser->name);
	return (msg_oks("oks"));
}
