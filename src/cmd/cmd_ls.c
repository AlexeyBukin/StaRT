/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 06:32:11 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_ls_scene(t_rt *rt, char *source)
{
	t_scn		*scn;
	char		*res;

	(void)source;
	if (rt == NULL || source == NULL)
		return (msg_err("Arguments are NULL"));
	if (*source != '\n' && *source != '\0')
		return (msg_oks("Unexpected arguments"));
	scn = rt->scene;
	if (scn == NULL)
		return (msg_err("Scene are NULL"));
	res = ft_strdup("Scene: objects[");
	res = ft_strjoin_free(res, ft_itoa(scn->objects_num));
	res = ft_strjoin_free(res, ft_strdup("]{"));
	res = ft_strjoin_free(res, ft_strdup("}"));
	return (msg_ok(res));
}

t_msg					cmd_ls_sphere(t_rt *rt, char *source)
{
	(void)rt;
	(void)source;
	return (msg_oks("This is ls sphere"));
}
