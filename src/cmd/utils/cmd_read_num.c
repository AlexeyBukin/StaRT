/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:46:20 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 07:04:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** cmd_read_num() moves source to end of num
** returns 0 on success
*/

int			cmd_read_num(char **source, t_num *num)
{
	char		*ptr;

	if (source == NULL)
		return (rt_err("Arguments are NULL"));
	if ((ptr = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (!ft_isnum(*ptr))
		return (-1);
	*num = (t_num)ft_atod(ptr);
	while (ft_isnum(*ptr))
		ptr++;
	*source = ptr;
	return (0);
}

int				cmd_read_vec2(char **source, t_vec2 *vec)
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

int				cmd_read_vec(char **source, t_vec3 *vec)
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
	err += cmd_read_comma(&str);
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	err += cmd_read_num(&str, &(vec->z));
	err += cmd_read_space(&str) < 0 ? -1 : 0;
	if (err < 0)
		return (rt_err("Syntax error: bad vector string"));
	if (!*str || *(str++) != '>')
		return (rt_err("Syntax error: expected \'>\'"));
	*source = str;
	return (0);
}

int 		cmd_read_matrix(char **source, t_mat3x3 *mtx)
{
	char		*str;

	if (source == NULL || mtx == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (!*str || *(str++) != '[')
		return (rt_err("Expected \'[\'"));
	if (cmd_read_vec(&str, &(mtx->x)))
		return (-1);
	cmd_read_comma(&str);
	cmd_read_space(&str);
	if (cmd_read_vec(&str, &(mtx->y)))
		return (-1);
	cmd_read_comma(&str);
	cmd_read_space(&str);
	if (cmd_read_vec(&str, &(mtx->z)))
		return (-1);
	if (!*str || *(str++) != ']')
		return (rt_err("Expected \']\'"));
	*source = str;
	return (0);
}

/*
** cmd_read_uint() moves source to end of num
** returns  0 on success
** returns -1 on error
** returns  1 on warning
*/

int			cmd_read_uint(char **source, uint *num)
{
	int			res;
	char		*ptr;

	if (source == NULL || num == NULL)
		return (rt_err("Arguments are NULL"));
	if ((ptr = *source) == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if ((res = ft_atoi(ptr)) <= 0)
		return (rt_warning("Bad uint", 1));
	*num = (uint)res;
	while (ft_isnum(*ptr))
		ptr++;
	*source = ptr;
	return (0);
}
