/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:46:20 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 07:04:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			cmd_read_vec2(char **source, t_vec2 *vec)
{
	int			err;
	char		*str;

	if (source == NULL || vec == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (!*str || *(str++) != '<')
		return (rt_err("Expected \'<\'"));
	err = 0;
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	err += cmd_read_num(&str, &(vec->x));
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	err += cmd_read_comma(&str);
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	err += cmd_read_num(&str, &(vec->y));
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	if (err < 0)
		return (rt_err("Syntax error: bad vector string"));
	if (!*str || *(str++) != '>')
		return (rt_err("Syntax error: expected \'>\'"));
	*source = str;
	return (0);
}

/*
** cmd_read_vec() moves source to end of vector
** returns 0 on success
*/

int			read_vec_part(char **str, t_vec3 *vec)
{
	int			err;

	if (str == NULL || vec == NULL)
		return (rt_err("given NULL pointer"));
	err = 0;
	err += cmd_read_space(str) < 0 ? -1 : 0;
	err += cmd_read_num(str, &(vec->x));
	err += cmd_read_space(str) < 0 ? -1 : 0;
	err += cmd_read_comma(str);
	err += cmd_read_space(str) < 0 ? -1 : 0;
	err += cmd_read_num(str, &(vec->y));
	err += cmd_read_space(str) < 0 ? -1 : 0;
	err += cmd_read_comma(str);
	err += cmd_read_space(str) < 0 ? -1 : 0;
	err += cmd_read_num(str, &(vec->z));
	err += cmd_read_space(str) < 0 ? -1 : 0;
	if (err < 0)
		return (rt_err("Syntax error: bad vector string"));
	return (0);
}

int			cmd_read_vec(char **source, t_vec3 *vec)
{
	char		*str;

	if (source == NULL || vec == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (!*str || *(str++) != '<')
		return (rt_err("Expected \'<\'"));
	if (read_vec_part(&str, vec))
		return (rt_err("Syntax error: bad vector string"));
	if (!*str || *(str++) != '>')
		return (rt_err("Syntax error: expected \'>\'"));
	*source = str;
	return (0);
}
