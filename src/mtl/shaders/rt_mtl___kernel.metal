/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mtl___kernel.metal                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:59:41 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/26 13:59:41 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <metal_stdlib>
using namespace metal;

typedef struct					s_gpu_info
{
	int a;
}								t_gpu_info;

typedef struct					s_gpu_obj
{
	int a;
}								t_gpu_obj;

typedef struct					s_gpu_mat
{
	int a;
}								t_gpu_mat;

//typedef struct					s_gpu_texture
//{
//	array<texture2d<float,access::read>, 2> texture [[id(0)]];
//}								t_gpu_texture;

typedef struct					s_gpu_texture
{
	texture2d<float,access::read> texture [[id(0)]];
//	texture2d<float,access::read> texture1 [[id(1)]];
}								t_gpu_texture;

typedef struct					s_gpu_scene
{
	device t_gpu_info			*info		[[id(0)]];
	device t_gpu_obj			*objects	[[id(1)]];
	device t_gpu_mat			*materials	[[id(2)]];
	device t_gpu_light			*light		[[id(3)]];
}								t_scene;

kernel void scene_test	(
							device t_scene					*scene		[[buffer(0)]],
							device t_gpu_texture			*textures	[[buffer(1)]],
							texture2d<float,access::write> 	out			[[texture(2)]],
							uint2                  			gid			[[thread_position_in_grid]]
						)
{
	{
		float4 color = textures[0].texture.read(gid);
		color += textures[1].texture.read(gid);
//		color /= 2;
//		float4 color = float4(0.5, 1, 0.5, 0.5);
		out.write(color, gid);
	}
}
