/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:09:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:13:14 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** cmd_parse_space() moves source to end of space sequence
** returns number of skipped spaces
** returns -1 on error
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
** returns  0 on success
** returns -1 on error
** returns  1 on warning (no any space)
*/

int			cmd_read_space_req(char **source)
{
	int		spaces;

	if (source == NULL)
		return (rt_err("Arguments are NULL"));
	spaces = cmd_read_space(source);
	if (spaces == 0)
	{
		if (*source == NULL)
			return (rt_err("Dereference to NULL"));
		if (**source != '\0' && **source != '\n')
			return (rt_warning("Syntax error: \' \' expected", 1));
	}
	return (0);
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

/*
** cmd_read_string() moves source to end of string
** returns 0 and sets dest to duplicated string on success
** returns  1 on warning
** returns -1 on error
*/

int			cmd_read_string(char **source, char **dest) //TODO use it for parse name
{
	char		*str;
	int			i;

	if (source == NULL || dest == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL"));
	i = 1;
	if (*str != '\"')
		return (rt_warning("Syntax error: Expected '\"' at the start of string", 1));
	while (str[i] != '\"' && str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\"')
		return (rt_warning("Syntax error: Expected '\"' at the end of string", 1));
	*source += i + 1;
	str = ft_strndup(str + 1, i - 1);
	if (str == NULL)
		return (rt_err("ft_strndup() returned NULL"));
	*dest = str;
	return (0);
}

