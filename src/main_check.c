//
// Created by Hugor Chau on 11/5/20.
//

#include "rt.h"

int				main()
{
	t_rt				*rt;
	uint					i = 0;

	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	scn_init(rt);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 1, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 2, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 3, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 4, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 5, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 6, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 7, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 8, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 9, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 10, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 11, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 12, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 13, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 14, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 15, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 16, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 17, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 18, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 19, 0);
	scn_add_sphere(rt->scene, (t_vec3){0, 0, 0}, 20, 0);
	while (i < rt->scene->objects_num)
	{
		ft_printf("r = %f\n", rt->scene->objects[i].shape.sphere.r);
		i++;
	}
	ft_printf("num = %i, num_max = %i\n", rt->scene->objects_num, rt->scene->objects_max);
	return (0);
}