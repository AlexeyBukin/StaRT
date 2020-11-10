/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:09:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 07:47:50 by kcharla          ###   ########.fr       */
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

	if (source == NULL)
		return (rt_err("Arguments are NULL"));
	spaces = cmd_read_space(source);
	if (spaces == 0)
	{
		if (*source == NULL)
			return (rt_err("Dereference to NULL"));
		if (**source != '\0' && **source != '\n')
			return (rt_err("Syntax error: \' \' expected"));
	}
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

/*
** cmd_read_string() moves source to end of string
** returns 0 and sets dest to duplicated string on success
*/

int			cmd_read_string(char **source, char **dest)
{
	char		*str;
	int			i;

	if (source == NULL || dest == NULL)
		return (rt_err("Arguments are NULL"));
	if ((str = *source) == NULL)
		return (rt_err("Dereference to NULL"));
	i = 1;
	if (*str != '\"')
		return (rt_err("Expected '\"' at the start of string"));
	while (str[i] != '\"' && str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\"')
		return (rt_err("Expected '\"' at the end of string"));
	*source += i + 1;
	str = ft_strndup(str + 1, i - 1);
	if (str == NULL)
		return (rt_err("ft_strndup() returned NULL"));
	*dest = str;
	return (0);
}

/*
** cmd_read_id_name() moves source to end of id uint or string
** returns error if no uint or string found
*/

int			cmd_read_id_name(t_rt *rt, char **source, uint *id)
{
	char		*name;

	if (rt == NULL || source == NULL || id == NULL)
		return (rt_err("Arguments are NULL"));
	if (*source == NULL)
		return (rt_err("Dereference to NULL"));
	if (**source == '\"')
	{
		if (cmd_read_string(source, &name))
			return (rt_err("Cannot read string"));
		//TODO implement scn_id_by_name()
		*id = 0;//scn_id_by_name(rt->scene, name);
		ft_free(name);
	}
	else
	{
		if (cmd_read_uint(source, id))
			return (rt_err("Cannot read uint"));
	}
	if (*id == 0)
		return (rt_err("Object cannot be specified"));
	return (0);
}
