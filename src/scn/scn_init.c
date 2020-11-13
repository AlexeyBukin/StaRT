/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/

int				scn_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("scn_init(): rt is NULL pointer"));
	if ((rt->scene = ft_memalloc(sizeof(t_scn))) == NULL)
		return (rt_err("scn_init(): malloc returned NULL pointer"));
	if ((rt->scene->id_to_name.elements = ft_memalloc(sizeof(t_element *) * MAP_STEP_SIZE)) == NULL)
		return (rt_err("scn_init(): malloc returned NULL pointer"));
	rt->scene->id_to_name.curr_size = MAP_STEP_SIZE;
	return (0);
}
