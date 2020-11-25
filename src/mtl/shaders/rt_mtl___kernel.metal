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

typedef struct					s_gpu_texture
{
	texture2d<float,access::read> texture [[id(0)]];
}								t_gpu_texture;

kernel void scene_test	(
							device t_gpu_info				*info		[[buffer(0)]],
							device t_gpu_obj				*objects	[[buffer(1)]],
							device t_gpu_mat				*materials	[[buffer(3)]],
							device t_gpu_texture			*textures	[[buffer(4)]],
							texture2d<float,access::write> 	out			[[texture(5)]],
							uint2                  			gid			[[thread_position_in_grid]]
						)
{
	{
		float4 color = textures[0].texture.read(gid);
//		float4 color = float4(0.5, 0.5, 0.5, 0.5);
//		color = float4(materials.test_float);
//		float4 color = float4(materials.exampleBuffer[0]);
		out.write(color, gid);
	}
}
