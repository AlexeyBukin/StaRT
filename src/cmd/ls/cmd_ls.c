/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_ls(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	parser->cur += ft_strlen("ls");
	if (scn_print(rt->scene))
		return (msg_warn("cmd_parse_command(): couldn\'t print objects"));
	return (msg_oks("It\'s for debug only"));
}

// t_msg					cmd_ls_scene(t_rt *rt, char *source)
// {
// 	t_scn		*scn;
// 	char		*res;

// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Arguments are NULL"));
// 	if (*source != '\n' && *source != '\0')
// 		return (msg_oks("Unexpected arguments"));
// 	scn = rt->scene;
// 	if (scn == NULL)
// 		return (msg_err("Scene are NULL"));
// 	res = ft_strdup("Scene: objects[");
// 	res = ft_strjoin_free(res, ft_itoa(scn->objects_num));
// 	res = ft_strjoin_free(res, ft_strdup("]{"));
// 	res = ft_strjoin_free(res, ft_strdup("}"));
// 	return (msg_ok(res));
// }

// t_msg					cmd_ls_sphere(t_rt *rt, char *source)
// {
// 	uint		id;
// 	char		*res;

// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Arguments are NULL"));
// //	if (cmd_read_space_req(&source) < 0)
// //		return (msg_warn("Syntax error: expected \' \'"));
// 	if (cmd_read_id_name(rt, &source, &id))
// 		return (msg_warn("Syntax error: expected correct id or name"));
// 	if (cmd_read_space(&source) < 0)
// 		return (msg_err("cmd_ls_sphere(): read error"));
// 	if (*source != '\n' && *source != '\0')
// 		return (msg_warn("Unexpected arguments"));
// 	//get object with given id
// 	res = ft_strdup("This id \'ls sphere\', id: \'");
// 	res = ft_strjoin_free(res, ft_itoa(id));
// 	res = ft_strjoin_free(res, ft_strdup("\'"));
// 	return (msg_ok(res));
// }
