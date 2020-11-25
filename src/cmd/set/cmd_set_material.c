//
// Created by Hugor Chau on 11/25/20.
//

#include "rt.h"

int 				cmd_set_material_default(t_rt *rt, t_parser *parser)
{
	(void)rt;
	if (parser == NULL)
		return (rt_err("cmd_set_camera_default(): was given a NULL pointer"));
	return (0);
}
