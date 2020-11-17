//
// Created by Hugor Chau on 11/16/20.
//

#include "rt.h"
#include "scn.h"

int		cam_init(t_cam **dest, char *name)
{
	t_cam		*cam;

	if (dest == NULL || name == NULL)
		return (rt_err("Given pointer is NULL"));
	if ((cam = (t_cam *)ft_memalloc(sizeof(t_cam))) == NULL)
		return (rt_err("cam_init(): malloc returned NULL pointer"));
	cam->name = name;///??? ft_strdup ???
	cam->fov = vec2(90, 50.6);
	tfm_init(&(cam->transform));
	cam->id = scn_id();
	*dest = cam;
	return (0);
}

int		cam_init_default(t_cam **dest)
{
	t_cam		*cam_default;

	if (cam_init(&cam_default, ft_strdup(DEFAULT_CAMERA_NAME)))
		return (rt_err("Cannot init camera"));
	cam_default->id = DEFAULT_CAMERA_ID;
	*dest = cam_default;
	return (0);
}

int		cam_deinit(t_cam *cam)
{
	if (cam == NULL)
		return (rt_err("NULL pointer at cam deinint"));
	ft_free(cam->name);
	ft_free(cam);
	return (0);
}
