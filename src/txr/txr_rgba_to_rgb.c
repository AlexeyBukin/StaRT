/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_rgba_to_rgb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 18:11:25 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "txr.h"

int					txr_rgba_to_rgb(t_txr *rgba, t_txr **rgb_dest)
{
	int				i;
	int				j;
	size_t			j_a;
	t_txr			*rgb;

	if (rgba == NULL || rgb_dest == NULL)
		return (rt_err("Null pointer"));
	if (txr_init(&rgb, ft_strdup(rgba->name),
		(t_size2){rgba->width, rgba->height}))
		return (rt_err("Cannot malloc rgb texture"));
	i = -1;
	while ((size_t)++i < rgb->height)
	{
		j = -1;
		j_a = 0;
		while ((size_t)++j < rgb->stride)
		{
			rgb->content[i * rgb->stride + j] =
				rgba->content[i * rgba->stride + j_a];
			j_a += j_a % 4 == 3 ? 1 : 0;
			j_a++;
		}
	}
	*rgb_dest = rgb;
	return (0);
}
