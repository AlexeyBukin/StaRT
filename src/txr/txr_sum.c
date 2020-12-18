/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/14 17:40:27 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_size(t_txr *lhs, t_txr *rhs, t_txr *target)
{
	if (lhs->width != rhs->width || lhs->width != target->width)
		return (rt_err("check_size(): textures width err"));
	if (lhs->height != rhs->height || lhs->height != target->height)
		return (rt_err("check_size(): textures height err"));
	if (lhs->stride != rhs->stride || lhs->stride != target->stride)
		return (rt_err("check_size(): textures stride err"));
	return (0);
}

void	check_if_target_default(t_txr *lhs, t_txr *target)
{
	if (target->width == 0 && target->height == 0)
	{
		target->width = lhs->width;
		target->height = lhs->height;
		target->stride = lhs->stride;
		target->type = lhs->type;
		target->content = (char *)ft_memalloc(sizeof(char) *
						target->stride * target->height);
	}
}

int		txr_sum(t_txr *lhs, t_txr *rhs, t_txr *target)
{
	size_t		i;
	size_t		texture_size;

	if (lhs == NULL || rhs == NULL || target == NULL)
		return (rt_err("txr_sum(): given NULL pointer"));
	check_if_target_default(lhs, target);
	if (check_size(lhs, rhs, target))
		return (rt_err("txr_sum(): textures sizes are not identical"));
	texture_size = target->stride * target->height;
	i = 0;
	while (i < texture_size)
	{
		target->content[i] = lhs->content[i] + rhs->content[i];
		i++;
	}
	return (0);
}

int		txr_sum_lst(t_list *src, t_txr *target)
{
	if (src == NULL || target == NULL)
		return (rt_err("txr_sum_lst(): fatal: given NULL pointer"));
	if (src->next)
	{
		if (txr_sum(*(t_txr **)(src->content),
				*(t_txr **)(src->next->content), target))
			return (rt_err("txr_sum_lst() error"));
		src = src->next;
	}
	while (src)
	{
		if (txr_sum(*(t_txr **)(src->content), target, target))
			return (rt_err("txr_sum_lst() error"));
		src = src->next;
	}
	return (0);
}
