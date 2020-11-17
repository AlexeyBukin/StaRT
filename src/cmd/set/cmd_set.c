/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 05:21:03 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 11:11:59 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** returns  0 on success
** returns -1 on error
** returns  1 on warning
*/

int				cmd_component_match_keyword(enum e_component_type type, char *word)
{
	if (word == NULL)
		return (-1);
	if (type == COMPONENT_OBJECT || type == COMPONENT_ANY)
	{
		if (ft_strequ(word, KW_SPHERE) || ft_strequ(word, KW_PLANE))
			return (0);
		if (ft_strequ(word, KW_CYLINDER) || ft_strequ(word, KW_CONE))
			return (0);
	}
	if (type == COMPONENT_MATERIAL || type == COMPONENT_ANY)
	{
		if (ft_strequ(word, KW_MATERIAL))
			return (0);	
	}
	//add camera and texture
	return (rt_warning("Component does not match keyword", 1));
}

// #define KW_COMPONENT_NUM 5

t_msg			cmd_set_start(t_scn *scn, char *str, t_set_fork *arr, int len)
{
	static char		*obj_keywords[KW_OBJECT_NUM] = {KW_SPHERE, KW_PLANE, KW_CYLINDER, KW_CONE};
	int				i;

	i = 0;
	while (i < KW_OBJECT_NUM)
	{
		if (ft_str_next_is(str, obj_keywords[i]))
			cmd_set_start_object();
		i++;
	}
	
}

t_msg			cmd_set_tree(t_scn *scn, char *str, t_set_fork *arr, int len)
{	
	int						i;
	int						ecode;
	enum e_component_type	type;
	t_component				comp;
	uint					id;

	if (scn == NULL || str == NULL || arr == NULL)
		return (msg_err("Entered NULL pointers"));
	i = 0;
	while (i < len)
	{
		if (ft_str_next_is(str, arr[i].word))
		{
			//got a component name_or_id
			str += ft_strlen(arr[i].word);
			if ((ecode = cmd_read_space_req(&str)))
			{
				if (ecode < 0)
					return (msg_err("Cannot read space"));
				return (msg_warn("Cannot read space"));
			}
			//get component id
			if ((ecode = cmd_read_id_name(scn, &str, &id)))
			{
				if (ecode < 0)
					return (msg_err("Cannot get id"));
				return (msg_warn("Cannot get id"));
			}
			//checking space after string
			if ((ecode = cmd_read_space_req(scn, &str, &id)))
			{
				if (ecode < 0)
					return (msg_err("Cannot read space"));
				return (msg_warn("Syntax error: \' \' expected"));
			}
			//get component type
			if ((ecode = scn_component_get_type(scn, id, &type)))
			{
				if (ecode < 0)
					return (msg_err("Cannot get component type"));
				return (msg_warn("Cannot get component type"));
			}
			//type component comparison
			if ((ecode = cmd_component_match_keyword(type, arr[i].word)))
			{
				if (ecode < 0)
					return (msg_err("Cannot compare component type"));
				return (msg_warn("Component does not match keyword"));
			}
			//getting tmp object

			if (type == COMPONENT_OBJECT)
				
			
			//call cmd_set_xxx func
			
			if (arr[i].func == NULL)
				return (msg_err("Given function pointer is NULL"));
			return (arr[i].func(rt, str));
		}
		i++;
	}
	return (msg_warn("Syntax error: Unknown keyword"));
}

#define KW_CMD_SET_OBJECT_NUM 4

t_msg			cmd_set_object(t_scn *scene, char *source)
{
	static t_set_fork	arr[KW_CMD_SET_OBJECT_NUM] = {
		(t_set_fork){&cmd_set_sphere, KW_SPHERE},
		(t_set_fork){&cmd_set_plane, KW_PLANE},
		(t_set_fork){&cmd_set_cylinder, KW_CYLINDER},
		(t_set_fork){&cmd_set_cone, KW_CONE}
	};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_set_tree(scene, source, arr, KW_CMD_SET_OBJECT_NUM));
}

t_msg			cmd_set(t_rt *rt, char *source)
{
	t_msg			tmp;
	t_parse_help	helper;
	
	tmp = cmd_parse_type_name(source, &helper);
	if (tmp.status != MSG_OK)
		return (tmp);
	ft_free(tmp.str);
	// check name on scene
	// check scene type with helper.type
	// copy scene component into helper.component


	//shared with "add" string processing

	// if no issues found load back to scene component from helper.component
		static t_set_fork	arr[KW_CMD_SET_NUM] = {
		(t_set_fork){&cmd_set_sphere, KW_SPHERE},
		(t_set_fork){&cmd_set_plane, KW_PLANE},
		(t_set_fork){&cmd_set_cylinder, KW_CYLINDER},
		(t_set_fork){&cmd_set_cone, KW_CONE}
		// (t_set_fork){&cmd_set_material, KW_MATERIAL}
		// (t_set_fork){&cmd_set_camera, KW_CAMERA}
	};

	if (rt == NULL || source == NULL)
		return (msg_err("Argument is NULL pointer"));
	return (cmd_set_tree(rt->scene, source, arr, KW_CMD_SET_NUM));
}

