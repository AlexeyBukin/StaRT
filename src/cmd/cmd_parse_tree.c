/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:07:24 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/10 04:40:27 by kcharla          ###   ########.fr       */
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
			str += ft_strlen(arr[i].word);
			if (cmd_read_space_req(&str) < 0)
				return (msg_warn("Syntax error: expected \' \'"));
			if (arr[i].func == NULL)
				return (msg_err("Given function pointer is NULL"));
			return (arr[i].func(rt, str));
		}
		i++;
	}
	return (msg_warn("Syntax error: Unknown keyword"));
}
