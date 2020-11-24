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

struct					Material
{
	array<texture2d<float>, 1>	albedo_map		[[id(0)]];
	device float				*exampleBuffer	[[id(1)]];
	float						test_float 		[[id(2)]];
};

kernel void scene_test(
//							texture2d<float,access::read>   source      [[texture(0)]],
							device Material					&materials	[[buffer(0)]],
							texture2d<float,access::write> 	out			[[texture(1)]],
							uint2                  			gid			[[thread_position_in_grid]])
{
	{
//		float4 color = source.read(gid);//[gid.y][gid.x];
		float4 color = materials.albedo_map[0].read(gid);
//		color = float4(materials.test_float);
//		float4 color = float4(materials.exampleBuffer[0]);
		out.write(color, gid);
	}
}
