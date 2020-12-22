/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_put_txr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		txr_put_txr(t_txr *main, t_txr *putme, t_size2 origin)
{
	size_t	i;
	size_t	j;

	if (main == NULL || putme == NULL)
		return (rt_err("Null pointer"));
	if (main->type != putme.type)
		return (rt_err("Textures have different types"));
	i = 0;
	while (i < putme->height && (i + origin.y) < main->height)
	{
		j = 0;
		while (j < putme->width && (j + origin.x) < main->width)
		{
			main->content
			[(i + origin.y) * main->stride + (j + origin.x)] =
					putme->content[i * putme->stride + j];
			j++;
		}
		i++;
	}
	return (0);
}
