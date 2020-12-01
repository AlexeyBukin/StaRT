//
// Created by Hugor Chau on 11/17/20.
//

#include "rt.h"

void	cameras_memmove(t_scn *scn, t_cam **cameras, t_cam *cam)
{
	size_t		i;

	i = 0;
	while (i < scn->cameras_num)
	{
		if (scn->cameras[i] == cam)
		{
			i++;
			continue ;
		}
		*cameras = scn->cameras[i];
		i++;
		cameras++;
	}
}

int		cam_del(t_scn *scn, t_cam *cam)
{
	t_cam		**cameras;

	if (!(cameras = (t_cam **)ft_memalloc(sizeof(t_cam *) * (scn->cameras_num - 1))))
		return (rt_err("cam_remove_by_name(): malloc crashed"));
	cameras_memmove(scn, cameras, cam);
	cam_deinit(cam);///TODO do we need this?
	free(scn->cameras);
	scn->cameras = cameras;
	scn->cameras_num--;
	return (0);
}

int		scn_remove_by_name_cam(t_scn *scn, char *name)
{
	t_cam		*cam_to_del;

	if (scn == NULL || name == NULL)
		return (rt_err("cam_remove_by_name(): was given a NULL pointer"));
	cam_to_del = scn_get_cam_by_name(scn, name);
	if (cam_to_del == NULL)
		return (rt_err("cam_remove_by_name(): there is no"
			" camera with given name"));
	return (cam_del(scn, cam_to_del));
}
