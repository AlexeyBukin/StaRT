/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/20 19:51:22 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg				cmd_add(t_parser *parser)
{
	char			*str;

	if (parser == NULL)
		return(msg_err("Given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
        return (msg_err("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "sphere"))
	{
		parser->cur += ft_strlen("sphere");
        return (cmd_add_sphere(parser));
	}
	// else if (ft_str_next_is(str, "plane"))
	// {
	// 	parser->cur += ft_strlen("plane");
    //     return (cmd_add_plane(parser));
	// }
	// else if (ft_str_next_is(str, "cylinder"))
	// {
	// 	parser->cur += ft_strlen("cylinder");
    //     return (cmd_add_cylinder(parser));
	// }
	// else if (ft_str_next_is(str, "cone"))
	// {
	// 	parser->cur += ft_strlen("cone");
    //     return (cmd_add_cone(parser));
	// }
	return (msg_warn("Syntax error: Unknown object type"));
}

// t_msg					cmd_add(t_rt *rt, char *source)
// {
// 	static t_parse_fw	arr[CMD_ADD_NUM] = {
// 		(t_parse_fw){cmd_add_sphere, KW_SPHERE},
// 		(t_parse_fw){cmd_add_plane, KW_PLANE},
// 		// (t_parse_fw){cmd_add_cylinder, KW_CYLINDER},
// 		// (t_parse_fw){cmd_add_cone, KW_CONE},
// 		// (t_parse_fw){cmd_add_material, KW_MATERIAL}
// 	};

// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Argument is NULL pointer"));
// 	return (cmd_parse_tree(rt, source, arr, CMD_ADD_NUM));
// }

// //TODO add -N name, -M material, -T tag, -G group

// t_msg					cmd_parse_object_param(t_scn *scn, t_obj *obj, char **source)
// {
// 	t_msg				result;
// 	t_obj				*sphere;
// 	t_msg				(*parse_func)(char **, t_obj *);

// 	if (scn == NULL || obj == NULL || source == NULL)
// 		return (msg_err("Entered NULL pointers"));
// 	if (*source == NULL)
// 		return (msg_err("Dereference to NULL pointer"));
	
// 	if (ft_str_next_is(*source, KW_PARAM_NAME))
// 		parse_func = cmd_parse_object_name;
// 	else if (ft_str_next_is(*source, KW_PARAM_MAT))
// 		parse_func = cmd_set_sphere_radius;
// 	else if (ft_str_next_is(*source, KW_PARAM_MAT))
// 		parse_func = cmd_set_object_material;
// 	else if (ft_str_next_is(source, KW_PARAM_NAME))
// 		parse_func = cmd_set_object_name;
// 	else
// 		return (msg_warn("Unknown flag"));
		
// 	while (*source != '\0' && *source != '\n')
// 	{
// 		if (ft_str_next_is(source, KW_PARAM_POS))
// 			parse_func = cmd_set_sphere_pos;
// 		else if (ft_str_next_is(source, KW_PARAM_RAD))
// 			parse_func = cmd_set_sphere_radius;
// 		else if (ft_str_next_is(source, KW_PARAM_MAT))
// 			parse_func = cmd_set_object_material;
// 		else if (ft_str_next_is(source, KW_PARAM_NAME))
// 			parse_func = cmd_set_object_name;
// 		else
// 			return (msg_warn("Unknown flag"));
// 		source += KW_PARAM_LEN;
// 		result = parse_func(&source, sphere);
// 		if (result.status != MSG_OK)
// 			return (result);
// 		// TODO why we have to free it?
// 		// Concatenate with next 	
// 		ft_free(result.str);
// 		if (cmd_read_space_req(&source))
// 			return (msg_warn("Expected \' \'"));
// 	}
// 	return (msg_oks("Added sphere"));
// }

// t_msg					cmd_add_sphere(t_rt *rt, char *source)
// {
// 	t_msg				result;
// 	t_obj				*sphere;
// 	t_msg				(*parse_func)(char **, t_obj *);

// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Entered NULL pointers"));
// 	result = (t_msg){MSG_NONE, NULL};

// 	if ((sphere = scn_create_object(rt->scene)) == NULL)
// 		return (msg_err("Cannot create object"));
		
// 	// scn have to init sphere to defaut values
// 	if (scn_set_default_sphere(sphere))
// 		return (msg_err("Cannot set default values"));
	
// 	while (*source != '\0' && *source != '\n')
// 	{
// 		if (ft_str_next_is(source, KW_PARAM_POS))
// 			parse_func = cmd_set_sphere_pos;
// 		else if (ft_str_next_is(source, KW_PARAM_RAD))
// 			parse_func = cmd_set_sphere_radius;
// 		else if (ft_str_next_is(source, KW_PARAM_MAT))
// 			parse_func = cmd_set_object_material;
// 		else if (ft_str_next_is(source, KW_PARAM_NAME))
// 			parse_func = cmd_set_object_name;
// 		else
// 			return (msg_warn("Unknown flag"));
// 		source += KW_PARAM_LEN;
// 		result = parse_func(&source, sphere);
// 		if (result.status != MSG_OK)
// 			return (result);
// 		// TODO why we have to free it?
// 		// Concatenate with next 	
// 		ft_free(result.str);
// 		if (cmd_read_space_req(&source))
// 			return (msg_warn("Expected \' \'"));
// 	}
// 	return (msg_oks("Added sphere"));
// }

// t_msg					cmd_add_plane(t_rt *rt, char *source)
// {
// 	t_msg				result;
// 	t_plane				*plane;
// 	t_msg				(*parse_func)(char **, t_plane *);
	
// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Entered NULL pointers"));
// 	result = (t_msg){MSG_NONE, NULL};

// 	t_plane			p;
// 	plane = &p;

// 	// plane = NULL;// TODO scn_get_obj(rt->scene);
// 	if (plane == NULL)
// 		return (msg_err("Given pointer is NULL"));

// 	// scn have to init sphere to defaut values

// 	while (*source != '\0' && *source != '\n')
// 	{
// 		if (ft_str_next_is(source, KW_PARAM_DIST))
// 			parse_func = cmd_set_plane_dist;
// 		else if (ft_str_next_is(source, KW_PARAM_RAD))
// 			parse_func = cmd_set_plane_dist;
// 		else if (ft_str_next_is(source, KW_PARAM_MAT))
// 			parse_func = cmd_set_plane_material; 
// 		else if (ft_str_next_is(source, KW_PARAM_NAME))
// 			parse_func = cmd_set_plane_name;
// 		else if (ft_str_next_is(source, KW_PARAM_NORM))
// 			parse_func = cmd_set_plane_norm;
// 		else
// 			return (msg_warn("Unknown flag"));
// 		source += KW_PARAM_LEN;
// 		result = parse_func(&source, plane);
// 		if (result.status == MSG_ERROR)
// 			return (result);
// 		if (cmd_read_space_req(&source))
// 			return (msg_warn("Expected \' \'"));
// 	}
// 	return (msg_oks("Added plane"));
// }

// t_msg					cmd_add_cylinder(t_rt *rt, char *source)
// {
// 	t_msg				result;
// 	t_cylinder			*cylinder;
// 	t_msg				(*parse_func)(char **, t_plane *);
	
// 	if (rt == NULL || source == NULL)
// 		return (msg_err("Entered NULL pointers"));
// 	result = (t_msg){MSG_NONE, NULL};

// 	t_plane			c;
// 	cylinder = &c;

// 	// plane = NULL;// TODO scn_get_obj(rt->scene);
// 	if (cylinder == NULL)
// 		return (msg_err("Given pointer is NULL"));

// 	// scn have to init sphere to defaut values

// 	while (*source != '\0' && *source != '\n')
// 	{
// 		if (ft_str_next_is(source, KW_PARAM_D))
// 			parse_func = cmd_set_plane_dist;
// 		else if (ft_str_next_is(source, KW_PARAM_R))
// 			parse_func = cmd_set_plane_dist;
// 		else if (ft_str_next_is(source, KW_PARAM_M))
// 			parse_func = cmd_set_plane_material; 
// 		else if (ft_str_next_is(source, KW_PARAM_NAME))
// 			parse_func = cmd_set_plane_name;
// 		else if (ft_str_next_is(source, KW_PARAM_NORM))
// 			parse_func = cmd_set_plane_norm;
// 		else
// 			return (msg_warn("Unknown flag"));
// 		source += KW_PARAM_LEN;
// 		result = parse_func(&source, plane);
// 		if (result.status == MSG_ERROR)
// 			return (result);
// 		if (cmd_read_space_req(&source))
// 			return (msg_warn("Expected \' \'"));
// 	}
// 	return (msg_oks("Added plane"));
// }

