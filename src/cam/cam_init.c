//
// Created by Hugor Chau on 11/16/20.
//

#include "rt.h"

int		cam_init(t_cam **cam, char *name)
{
	t_cam		*init_cam;

	if (!(init_cam = (t_cam *)ft_memalloc(sizeof(t_cam)))
		return (rt_err("cam_init(): malloc returned NULL pointer"));
	if (!(init_cam->name = ft_strdup(name)))
	{
		ft_memdel(&init_cam);
		return (rt_err("cam_init(): malloc returned NULL pointer"));
	}
	init_cam->fov = vec2(90, 50.6);
	tfm_init(&(init_cam->transform));
	init_cam->id = DEFAULT_CAMERA_ID;
	(*cam) = init_cam;
	return (0);
}

int		cam_deinit(t_cam **cam)
{
	ft_strdel(&(*cam)->name);
	ft_memdel((void **)cam);
	return (0);
}
