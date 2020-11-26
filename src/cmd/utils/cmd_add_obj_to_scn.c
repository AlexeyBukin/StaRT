//
// Created by Hugor Chau on 11/26/20.
//

#include "rt.h"

t_msg		cmd_add_obj_to_scn(t_rt *rt, t_parser *parser)
{
	if (parser->object->type != OBJ_GROUP)
	{
		parser->object->content.container.material = parser->material;
	//	parser->object->content.container.texture = parser->texture;//?? where to put?
	}
	if (scn_add_to_group(rt->scene, parser->group, parser->object))
		return (msg_oks("couldn\'t add obj to scene"));
	return (msg_oks("added object to scene successfully"));
}
