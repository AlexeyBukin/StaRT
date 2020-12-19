/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    rt_trace_mode_color_only.metal                     :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2020/09/17 15:45:55 by wpoudre           #+#    #+#              */
/*    Updated: 2020/09/17 15:45:58 by wpoudre          ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include <metal_stdlib>
using namespace metal;

float3			cook_torrance_ggx(float3x3 tmp, device t_gpu_texture *textures, device t_mat_pbr *m, thread t_obj &near, float3 pos)
{
	float		g;
	float3		f_diffk;
	float		n_dot_v;
	float		n_dot_l;
	float3		speck;
	float3		n;
	float3		l;
	float3		v;
	float3		color;

	n = normalize(tmp[0]);
	l = normalize(tmp[1]);
	v = normalize(tmp[2]);
	n_dot_v = dot(n, v);
	n_dot_l = dot(n, l);
	if (n_dot_l <= 0 || n_dot_v <= 0)
		return (float3(0));
	g = ggx_partial_geometry(n_dot_v, pow(m->roughness, 2));
	g = g * ggx_partial_geometry(n_dot_l, pow(m->roughness, 2));
	f_diffk = fresnel_schlick(m->f0, dot(normalize(v + l), v));
	speck = f_diffk * (g * ggx_distribution(dot(n, normalize(v + l)), pow(m->roughness, 2)) * 0.25 / (n_dot_v + 0.001));
	f_diffk = vec_clamp((float3(1.0) - f_diffk), 0.0, 1.0);
	if (m->albedo_txr_index < 0)
		f_diffk = m->albedo * f_diffk;
	else
		f_diffk = get_color_from_texture(pos, obj, &textures[m->albedo_txr_index]) * f_diffk;
	f_diffk = f_diffk * (n_dot_l / pi);
	return (speck + f_diffk);
}

float3	rt_trace_mode_ggx_loop(t_ggx_loop info, device t_gpu_texture *textures, device t_scn *scene, thread t_obj &near)
{
	float3					to_light;
	float3					to_view;
	thread float 			dist_to_shadow;
	thread struct s_obj 	nearest;
	float					dist_to_light;
	float					light_amount;

	nearest = near;
	if (ray_point_is_behind(info.normal, float3(scene->lights[info.light_id].pos)))
		return (float3(0));
	to_light = float3(scene->lights[info.light_id].pos) - info.normal.pos;
	dist_to_light = length(to_light);
	dist_to_shadow = 0.0;
	rt_trace_nearest_dist(scene, Ray(info.normal.pos, to_light), dist_to_shadow, nearest);
	if (dist_to_shadow > 0.00000001)
	{
		if (dist_to_shadow < dist_to_light)
		{
			return (float3(0.0));
		}
	}
	to_view = float3(info.cam_ray.dir) * -1;
	light_amount = scene->lights[info.light_id].power / (dist_to_light * dist_to_light + 1);
	return (cook_torrance_ggx(float3x3(info.normal.dir, to_light, to_view), &scene->materials[nearest.material_id].content.pbr, near, info.normal.pos) * light_amount);
}

static t_color			rt_trace_mode_ggx(device t_scn *scene, device t_gpu_texture *textures, thread struct s_obj &nearest,thread Ray &cam_ray)
{
	thread float 		dist;
	Ray					normal;
	int					i;
	float3				res;


	i = rt_trace_nearest_dist(scene, cam_ray, dist, nearest);
	if (dist == INFINITY)
		return (float4(0));
	normal.pos = cam_ray.pos + cam_ray.dir * dist;
	normal.dir = trace_normal_fig(cam_ray, &scene->objects[i], dist);
	res = float3(0.0f);
	i = 0;
	while (i < scene->info->light_num)
	{
		res = res + rt_trace_mode_ggx_loop((t_ggx_loop){normal, cam_ray, i, nearest.material_id}, scene, nearest);
		i++;
	}
	res = vec_clamp(res, 0, 1);
	cam_ray.pos = normal.pos + 0.001;
	cam_ray.dir = normalize(-2 * dot(cam_ray.dir, normal.dir) * normal.dir + cam_ray.dir);
	return (col_from_vec_norm(vec_to_srgb(res)));
}

kernel void trace_mod_ggx(	device t_scn					*scene		[[buffer(0)]],
							device t_gpu_texture			*textures	[[buffer(1)]],
							texture2d<float,access::write> 	out			[[texture(2)]],
							uint2                  			gid			[[thread_position_in_grid]])
{
	thread Ray			ray;
	float4				color = {0};
	float				r;
	float4				res_color;
	thread struct s_obj	nearest;
	float 				k = 0.0;
	device struct s_cam	*cam = &scene->info->camera;
	uint2				size = uint2(out.get_width(), out.get_height());
	float2				tmp = map2(float2(gid.x, gid.y), float4(float2(0.0f, (float)size.x), float2(0.0f, (float)size.y)), float4(float2(-1 * (float)size.x / 2, (float)size.x / 2), float2(-1 * (float)size.y / 2, (float)size.y / 2)));
	float2				ls;
	float4				cl = {0};
	int					i;

	nearest.id = -1;
	for (int s = 0; s < 100; ++s)
	{
		ls = tmp;
		ray = Ray(cam->pos, normalize(float3(ls.x + rand(1 + s, 1 - s, 1 * s), ls.y + rand(1 * s, 1 - s, 1 + s), 1000.0 + rand(1 - s, 1 * s, 1 + s))));
		k = 0.0;
		nearest.id = -1;
		cl = float4(0);
		res_color = float4(0.5);
		while (k < 1.0 && length(res_color) > 0.0)
		{
			res_color = rt_trace_mode_ggx(scene, nearest, ray);
			if (nearest.material_id < 0)
				break;
			cl = colors_mix(cl, k, res_color, scene->materials[nearest.material_id].content.pbr.roughness - k);
			k += scene->materials[nearest.material_id].content.pbr.roughness;
		}
		color += cl;
	}
	color *= (1.0 / 100.0);
	color.w = 1;
	out.write(color, gid);
}

