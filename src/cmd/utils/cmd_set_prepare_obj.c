//
// Created by Hugor Chau on 11/26/20.
//

#include "rt.h"

int 		cmd_set_prepare_obj(t_parser *parser, t_obj *src)
{
	if (!(parser->object = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (rt_err("cmd_set_cone(): malloc error"));
	ft_memcpy(parser->object, src, sizeof(t_obj));
	parser->name = ft_strdup(src->name);
	parser->transform = &parser->object->transform;
	parser->container = &parser->object->content.container;
	parser->material = src->content.container.material;
	return (0);
}
