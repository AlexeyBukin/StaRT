/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "scn.h"

int		cam_init(t_obj **dest, char *name)
{
	t_obj		*tmp;

	if (dest == NULL || name == NULL)
		return (rt_err("cam_init_default(): given NULL pointer"));
	tmp = ft_memalloc(sizeof(t_obj));
	if (tmp == NULL)
		return (rt_err("Cannot malloc object copy"));
	tmp->id = scn_id();
	tmp->name = name;
	tmp->parent = NULL;
	tmp->visible = TRUE;
	tmp->type = OBJ_CAMERA;
	tfm_init(&(tmp->transform));
	tmp->transform.parent = NULL;
	tmp->content.camera.fov = vec2(90, 50.6);
	*dest = tmp;
	return (0);
}

int		cam_init_default(t_obj **dest)
{
	t_obj		*cam_default;
	char		*default_name;

	if (dest == NULL)
		return (rt_err("cam_init_default(): given NULL pointer"));
	if ((default_name = ft_strdup(DEFAULT_CAMERA_NAME)) == NULL)
		return (rt_err("cam_init_default(): malloc error"));
	if (cam_init(&cam_default, default_name))
	{
		free(default_name);
		return (rt_err("Cannot init camera"));
	}
	cam_default->id = DEFAULT_CAMERA_ID;
	*dest = cam_default;
	return (0);
}

int		cam_deinit(t_obj *cam)
{
	if (cam == NULL)
		return (rt_err("NULL pointer at cam deinint"));
	ft_free(cam->name);
	ft_free(cam);
	return (0);
}
