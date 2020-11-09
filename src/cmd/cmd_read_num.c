/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:46:20 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 01:46:20 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: rewrite to return int error code
** cmd_read_num() moves source to end of num
** returns INFINITY on error
*/

t_num		cmd_read_num(char **source)
{
	t_num		res;
	char		*ptr;

	if (source == NULL)
		return ((t_num)INFINITY);
	if ((ptr = *source) == NULL)
		return ((t_num)INFINITY);
	res = (t_num)ft_atod(ptr);
	while (ft_isnum(*ptr))
		ptr++;
	*source = ptr;
	return (res);
}

/*
** cmd_read_vec() moves source to end of vector
** returns 0 on success
*/

int				cmd_read_vec(char **source, t_vec3 *vec)
{
	int			err;
	char		*str;

	if (source == NULL || vec == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (*(str++) != '<')
		return (rt_err("Expected \'<\'"));
	err = 0;
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	vec->x = cmd_read_num(&str);
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	err += cmd_parse_comma(&str) < 0 ? -1 : 0;
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	vec->y = cmd_read_num(&str);
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	err += cmd_parse_comma(&str) < 0 ? -1 : 0;
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	vec->z = cmd_read_num(&str);
	err += cmd_parse_space(&str) < 0 ? -1 : 0;
	if (err < 0)
		return (rt_err("Syntax error: bad vector string"));
	if (*(str++) != '>')
		return (rt_err("Syntax error: expected \'>\'"));
	*source = str;
	return (0);
}
