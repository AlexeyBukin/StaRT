
#include "rt.h"

t_msg				set_error(t_parser *parser, char *message)
{
	obj_deinit(parser->object);
//	ft_free(parser->name);
	return (msg_warn(message));
}

t_msg			cmd_set_obj_to_scn(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL || dest == NULL)
		return (msg_warn("cmd_set_obj_to_scn(): given NULL pointer"));
	ft_memcpy(dest, parser->object, sizeof(t_obj));
	dest->name = ft_strdup(parser->name);
	dest->transform.rot_local.x = vec3_normalize(dest->transform.rot_local.x);
	dest->transform.rot_local.y = vec3_normalize(dest->transform.rot_local.y);
	dest->transform.rot_local.z = vec3_normalize(dest->transform.rot_local.z);
	if (dest->type != OBJ_GROUP)
	{
		dest->content.container.material = parser->material;
	}
	if (parser->group != dest->parent && parser->group != NULL)
	{
		scn_move_obj(rt->scene, parser->group, dest);
	}
	obj_deinit(parser->object);
	ft_free(parser->name);
	return (msg_oks("oks"));
}
