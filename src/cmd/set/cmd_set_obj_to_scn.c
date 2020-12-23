/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_obj_to_scn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg			cmd_set_txr_read(t_parser *parser, t_txr *dest)
{
	t_txr		*txr;

	if (fio_png_read_name(&txr,
				ft_strdup(parser->texture->filename), ft_strdup(parser->name)))
	{
		ft_free(parser->name);
		ft_free(parser->texture);
		return (msg_warn("png read error"));
	}
	if (parser->texture->type != txr->type)
	{
		txr_deinit(txr);
		txr_deinit(parser->texture);
		return (msg_warn("png type error"));
	}
	ft_free(parser->name);
	ft_free(parser->texture);
	ft_free(dest->name);
	ft_free(dest->filename);
	if (dest->content)
		ft_free(dest->content);
	ft_memcpy(dest, txr, sizeof(t_txr));
	return (msg_oks("set txr success"));
}

t_msg			cmd_set_txr_to_scn(t_parser *parser, t_txr *dest)
{
	if (parser->texture->filename)
	{
		return (cmd_set_txr_read(parser, dest));
	}
	ft_free(dest->name);
	dest->name = parser->name;
	dest->type = parser->texture->type;
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

int				cmd_move_obj(t_rt *rt, t_parser *parser, t_obj *dest)
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
