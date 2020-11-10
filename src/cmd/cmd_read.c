/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:09:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 02:52:54 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** cmd_parse_space() moves source to end of space sequence
** returns number of skipped spaces
*/

int			cmd_read_space(char **source)
{
	char	*str;
	int		i;

	if (source == NULL)
		return (rt_err("cmd_parse_space(): source is NULL pointer"));
	if (*source == NULL)
		return (rt_err("cmd_parse_space(): dereference to NULL pointer"));
	str = *source;
	i = 0;
	while (*str == ' ')
	{
		str++;
		i++;
	}
	*source = str;
	return (i);
}


/*
** cmd_parse_space_req() moves source to end of space sequence
** returns error if no spaces was skipped
*/

int			cmd_read_space_req(char **source)
{
	int		spaces;

	spaces = cmd_read_space(source);
	if (spaces == 0)
		return (rt_err("Syntax error: \' \' expected"));
	return (spaces);
}

/*
** cmd_read_comma() moves source by 1 char if comma found
** returns error if no comma found
*/

int			cmd_read_comma(char **str)
{
	if (str == NULL)
		return (rt_err("Arguments are NULL"));
	if (*str == NULL)
		return (rt_err("Dereference to NULL pointer"));
	if (*(*str) != ',')
		return (rt_err("Syntax error: expected \',\'"));
	(*str)++;
	return (0);
}
