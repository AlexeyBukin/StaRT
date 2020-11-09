/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/09 16:16:50 by jvoor            ###   ########.fr       */
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
	rt->scene->objects_max = 0;
	return (0);
}
