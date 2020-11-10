/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 02:37:26 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** TODO: add parser
** TODO: add id-map pattern
*/

/*
** work with string as single command, so need to manage it in one move
** when we get word we try to:
** 1) find out is it command ( else unknown command quit)
** 1.1) extra funcs for each command for better err managment
** 2) find out is it arg (if args is invalid - quit err invalid args)
** 3) find out is it flags (ignore invalid flags)
** 4) check out values associated with flags is it valid
**		(if not - set default vals)
*/

/*
**  TODO: fill arr in cmd_parse_add
*/

t_msg					cmd_parse_add(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_ADD_NUM] =
	{(t_parse_fw){cmd_add_sphere, KW_SPHERE}};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_MAIN_NUM));
}

t_msg					cmd_parse_ls(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_LS_NUM] =
	{(t_parse_fw){&cmd_ls_scene, KW_SCENE}, (t_parse_fw){&cmd_ls_sphere, KW_SPHERE}};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_LS_NUM));
}

t_msg					cmd_parse_rm(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_LS_NUM] =
			{(t_parse_fw){&cmd_ls_scene, KW_SCENE}, (t_parse_fw){&cmd_ls_sphere, KW_SPHERE}};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_LS_NUM));
}

t_msg					cmd_parse_set(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_LS_NUM] =
			{(t_parse_fw){&cmd_ls_scene, KW_SCENE}, (t_parse_fw){&cmd_ls_sphere, KW_SPHERE}};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_LS_NUM));
}

t_msg					cmd_parse_line(t_rt *rt, char *source)
{
	static t_parse_fw	arr[CMD_MAIN_NUM] =
	{(t_parse_fw){&cmd_parse_add, KW_ADD}, (t_parse_fw){&cmd_parse_ls, KW_LS},
	(t_parse_fw){&cmd_parse_rm, KW_RM}, (t_parse_fw){&cmd_parse_set, KW_SET}};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_parse_tree(rt, source, arr, CMD_MAIN_NUM));
}
