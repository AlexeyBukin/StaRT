/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by jvoor             #+#    #+#             */
/*   Updated: 2020/11/13 01:31:46 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define KW_CAP "-c"
#define KW_PARAM_P "-p"
#define KW_PARAM_R "-r"
#define KW_PARAM_M "-m"
#define KW_PARAM_NAME "-N"
#define KW_PARAM_NORM "-n"
#define KW_PARAM_D "-d"

#define KW_PARAM_LEN 2

t_msg					cmd_add_sphere(t_rt *rt, char *source)
{
	t_msg				result;
	t_sphere			*sphere;
	t_msg				(*parse_func)(char **, t_sphere *);

	if (rt == NULL || source == NULL)
		return (msg_err("Entered NULL pointers"));
	result = (t_msg){MSG_NONE, NULL};

	t_sphere	s;
	sphere = &s;

	// sphere = NULL;// TODO scn_get_obj(rt->scene);
	if (sphere == NULL)
		return (msg_err("Given pointer is NULL"));

	// scn have to init sphere to defaut values

	while (*source != '\0' && *source != '\n')
	{
		if (ft_str_next_is(source, KW_PARAM_P))
			parse_func = cmd_set_sphere_pos;
		else if (ft_str_next_is(source, KW_PARAM_R))
			parse_func = cmd_set_sphere_radius;
		else if (ft_str_next_is(source, KW_PARAM_M))
			parse_func = cmd_set_sphere_material;
		else if (ft_str_next_is(source, KW_PARAM_NAME))
			parse_func = cmd_set_sphere_name;
		else
			return (msg_warn("Unknown flag"));
		source += KW_PARAM_LEN;
		result = parse_func(&source, sphere);
		if (result.status == MSG_ERROR)
			return (result);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Added sphere"));
}

t_msg					cmd_add_plane(t_rt *rt, char *source)
{
	t_msg				result;
	t_plane				*plane;
	t_msg				(*parse_func)(char **, t_plane *);
	
	if (rt == NULL || source == NULL)
		return (msg_err("Entered NULL pointers"));
	result = (t_msg){MSG_NONE, NULL};

	t_plane			p;
	plane = &p;

	// plane = NULL;// TODO scn_get_obj(rt->scene);
	if (plane == NULL)
		return (msg_err("Given pointer is NULL"));

	// scn have to init sphere to defaut values

	while (*source != '\0' && *source != '\n')
	{
		if (ft_str_next_is(source, KW_PARAM_D))
			parse_func = cmd_set_plane_dist;
		else if (ft_str_next_is(source, KW_PARAM_R))
			parse_func = cmd_set_plane_dist;
		else if (ft_str_next_is(source, KW_PARAM_M))
			parse_func = cmd_set_plane_material; 
		else if (ft_str_next_is(source, KW_PARAM_NAME))
			parse_func = cmd_set_plane_name;
		else if (ft_str_next_is(source, KW_PARAM_NORM))
			parse_func = cmd_set_plane_norm;
		else
			return (msg_warn("Unknown flag"));
		source += KW_PARAM_LEN;
		result = parse_func(&source, plane);
		if (result.status == MSG_ERROR)
			return (result);
		if (cmd_read_space_req(&source))
			return (msg_warn("Expected \' \'"));
	}
	return (msg_oks("Added plane"));
}

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

