/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:17:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:36:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned char 	*get_texture_rgba_fine_64();
unsigned char	*get_texture_rgba_empty_64();
void 			fill_mat_pbr(t_gpu_mat *mat);
void 			fill_mat_pbr2(t_gpu_mat *mat);
int				gpu_init(t_gpu **gpu_dest);
void 			fill_obj_sphere(t_gpu_obj *obj);
void 			fill_obj_cone(t_gpu_obj *obj);
void			fill_light(t_gpu_light *lig);
//int				fio_png_write(char *data, int width, int height, char *filename);

int				gpu_render(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	if (gpu_buffer_materials_init(rt->gpu, rt->scene))
		return (rt_err("Cannot init materials buffer"));

	rt->gpu->info.camera.pos = vec3_zero();
	rt->gpu->info.camera.rot_axis = mat3x3_identity();
	rt->gpu->info.camera.fov = (t_vec2){90, 50};
	rt->gpu->info.camera.id = 0;

	rt->gpu->info.mat_num = 2;
	rt->gpu->mat_buf = ft_malloc(sizeof(t_gpu_mat) * rt->gpu->info.mat_num);
	fill_mat_pbr(&(rt->gpu->mat_buf[0]));
	fill_mat_pbr2(&(rt->gpu->mat_buf[1]));

	rt->gpu->info.obj_num = 2;
	rt->gpu->obj_buf = ft_malloc(sizeof(t_gpu_obj) * rt->gpu->info.obj_num);
	fill_obj_sphere(&(rt->gpu->obj_buf[0]));
	fill_obj_cone(&(rt->gpu->obj_buf[1]));

//	rt->gpu->lgt_buf = ft_memalloc(sizeof(t_gpu_light));
//	fill_light(rt->gpu->lgt_buf);
//	rt->gpu->info.lgt_num = 1;

//	if (gpu_buffer_materials_init(rt->gpu, rt->scene))
//		return (rt_err("Cannot init materials buffer"));
//	if (gpu_buffer_objects_init(rt->gpu, rt->scene))
//		return (rt_err("Cannot init objects buffer"));
//	if (gpu_buffer_lights_init(rt->gpu, rt->scene))
//		return (rt_err("Cannot init lights buffer"));
//	// Load textures
	if (gpu_buffer_load(rt->gpu))
		return (rt_err("Cannot load buffers to GPU"));
	if (gpu_kernel_run(rt->gpu))
		return (rt_err("Cannot run kernel"));
	return (0);
}


void 			fill_mat_pbr(t_gpu_mat *mat)
{
	mat->id = 0;
	mat->type = MAT_PBR;

	mat->content.pbr.albedo = vec3(0.73, 0.93, 0.0);
	mat->content.pbr.f0 = vec3(0.0, 0.0, 0.0);
	mat->content.pbr.metalness = 0.0;
	mat->content.pbr.roughness = 0.7;
	mat->content.pbr.transparency = 0.0;
	mat->content.pbr.ior = 1.6;

	mat->content.pbr.albedo_txr_index = 0;
	mat->content.pbr.f0_txr_index = -1;
	mat->content.pbr.metalness_txr_index = -1;
	mat->content.pbr.roughness_txr_index = -1;
	mat->content.pbr.transparency_txr_index = -1;
	mat->content.pbr.normal_txr_index = 1;
}

void 			fill_mat_pbr2(t_gpu_mat *mat)
{
	mat->id = 1;
	mat->type = MAT_PBR;

	mat->content.pbr.albedo = vec3(0.6, 0.6, 0.6);
	mat->content.pbr.f0 = vec3(0.0, 0.0, 0.0);
	mat->content.pbr.metalness = 0.0;
	mat->content.pbr.roughness = 1.0;
	mat->content.pbr.transparency = 0.0;
	mat->content.pbr.ior = 1.6;

	mat->content.pbr.albedo_txr_index = 0;
	mat->content.pbr.f0_txr_index = -1;
	mat->content.pbr.metalness_txr_index = -1;
	mat->content.pbr.roughness_txr_index = -1;
	mat->content.pbr.transparency_txr_index = -1;
	mat->content.pbr.normal_txr_index = 1;
}

void 			fill_obj_sphere(t_gpu_obj *obj)
{
	obj->id = 0;
	obj->mat_index = 0;
	obj->map_axis = mat3x3_identity();
	obj->type = SHP_SPHERE;
	obj->shape.sphere.pos = vec3(5, -5, 20);
	obj->shape.sphere.r = 2;
}

void 			fill_obj_cone(t_gpu_obj *obj)
{
	obj->id = 1;
	obj->mat_index = 1;
	obj->type = SHP_CONE;
	obj->shape.cone.pos = vec3(0, 5, 15);
	obj->shape.cone.cap = vec3(0, -5, 15);
	obj->shape.cone.r = 3;
}

//add light "l1" -p <0, 0, 30> -c <1, 1, 1> -i 500.0

void			fill_light(t_gpu_light *lig)
{
	lig->id = 0;
	lig->col = vec3(1.0, 1.0, 1.0);
	lig->pos = vec3(0, 0, 30);
	lig->power = 500;
}

unsigned char *get_texture_rgba_fine_64()
{
	int i;
	int j;
	int w = 64;
	int h = 64;
	int stride = w * 4;
	unsigned char *texture_rbga = ft_malloc(sizeof(unsigned char) * stride * h);
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
		{
			int pixnum = i * stride + j * 4;
			texture_rbga[pixnum + 0] = (pixnum % 2 == 0 ? 127 : 0) + (pixnum % 4 == 0 ? 127 : 0);
			texture_rbga[pixnum + 1] = (pixnum % 2 == 1 ? 127 : 0) + (pixnum % 8 == 0 ? 127 : 0);
			texture_rbga[pixnum + 2] = (pixnum % 2 == 0 ? 127 : 0) + (pixnum % 16 == 0 ? 127 : 0);
			texture_rbga[pixnum + 3] = 255;
		}
	return (texture_rbga);
}

unsigned char *get_texture_rgba_empty_64()
{
	int i;
	int j;
	int w = 64;
	int h = 64;
	int stride = w * 4;
	unsigned char *texture_rbga = ft_malloc(sizeof(unsigned char) * stride * h);
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
		{
			int pixnum = i * stride + j * 4;
			texture_rbga[pixnum + 0] = 0;
			texture_rbga[pixnum + 1] = (0);
			texture_rbga[pixnum + 2] = (0);
			texture_rbga[pixnum + 3] = 255;
		}
	return (texture_rbga);
}

