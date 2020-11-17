//
// Created by Hugor Chau on 11/17/20.
//

#include "rt.h"

int		cam_add(t_scn *scn, t_cam *cam)
{
	t_cam		**new_array;
	t_cam		*cam_copy;

	if (!scn || !cam)
		return (rt_err("cam_add(): was given a NULL pointer"));
	if ((cam_copy = scn_get_cam_by_name(scn, cam->name)) || scn_name_check(scn, cam->name))
	{
//		if (cam_copy == cam)
//			return (rt_err("cam_add(): object is inside the scene already"));
		return (rt_err("cam_add(): name collision"));
	}
	if (!(new_array = (t_cam **)ft_realloc(scn->cameras, sizeof(t_cam *) * scn->cameras_num,
										   sizeof(t_cam *) * (scn->cameras_num + 1))))
		return (rt_err("cam_add(): malloc returned NULL pointer"));
	scn->cameras = new_array;
	scn->cameras_num++;
	scn->cameras[scn->cameras_num - 1] = cam;
	return (0);
}
