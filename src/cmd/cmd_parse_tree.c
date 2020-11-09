/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:07:24 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/09 22:22:01 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg			cmd_parse_tree(t_rt *rt, char *str, t_parse_fw *arr, int len)
{	
	int			i;
	t_parse_fw	curr;

	if (rt == NULL || str == NULL || arr == NULL)
		return (msg_err("Entered NULL pointers"));
	curr = (t_parse_fw){NULL, NULL};
	i = 0;
	while (i < len)
	{
		if (ft_str_next_is(str, arr[i].word))
		{
			curr = arr[i];
			break ;
		}
	}
	if (ft_str_next_is(str, " "))//TODO: add multispace managment
		return (msg_err("Unknown argument: expected \' \'"));
	if (curr.func == NULL)
		return (msg_err("Given function pointer is NULL"));
	str += ft_strlen(curr.word) + 1;
	return (curr.func(rt, str));
}
