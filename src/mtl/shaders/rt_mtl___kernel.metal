# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rt_mtl___kernel.metal                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 13:59:41 by kcharla           #+#    #+#              #
#    Updated: 2020/12/14 17:17:39 by rtacos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include <metal_stdlib>
using namespace metal;

constant const float pi = 3.14159265358979323846f;

enum e_obj_type
{
	OBJ_NONE = 0,
	OBJ_PLANE,
	OBJ_SPHERE
};

struct				s_sphere
{
	packed_float3	pos;
	float			r;
};

struct				s_plane
{
	packed_float3	n;
	float			d;
};

union				u_shape
{
	struct s_sphere		sphere;
	struct s_plane		plane;
};

struct				s_obj
{
	int					id;
	int					material_id;
	enum e_obj_type		type;
	union u_shape		shape;
};

struct				s_cam
{
	int				id;
	packed_float3	pos;
	packed_float3	forward;
	packed_float3	up;
	packed_float3	right;
	packed_float2	fov;
};

struct				s_mat
{
	int				id;
	float 			metalness;
	float 			roughness;
	float 			ior;
	float 			transparency;
	packed_float3	albedo;
	packed_float3	f0;
};

typedef struct		s_scn
{
	device t_gpu_info			*info		[[id(0)]];
	device t_gpu_obj			*objects	[[id(1)]];
	device t_gpu_mat			*materials	[[id(2)]];
	device t_gpu_light			*light		[[id(3)]];
}								t_scene;

kernel void scene_test(		device struct		s_scn		*scene		[[buffer(0)]],
							device struct		s_obj		*objects	[[buffer(1)]],
							device struct		s_mat		*materials	[[buffer(2)]],
							texture2d<float,access::write> 	out			[[texture(3)]],
							uint2                  			gid			[[thread_position_in_grid]])
{
	uint2 size = uint2(out.get_width(), out.get_height());
	device struct s_cam *cam = &scene->camera;

	if (gid.x < size.x && gid.y < size.y)
	{
		float4 color = float4(0.5, 0.5, 0.5, 0);

//		Ray ray = rt_camera_get_ray(cam, size, gid);
//
//		int		nearest_id = -1;
//		float	nearest_dist = INFINITY;
//
//		for (int i = 0; i < scene->objects_num; i++)
//		{
//			float dist = rt_dist(ray, &scene->objects[i]);
//			if (dist < nearest_dist && dist != INFINITY) {
//				nearest_id = i;
//				nearest_dist = dist;
//			}
//		}
//
//		if (nearest_id >= 0) {
////			color = float4(0, 1, 0, 0);
//			int index = find_material_by_id(
//					scene->objects[nearest_id].material_id,
//					scene->materials, scene->materials_num);
//			if (scene->materials_num == 1) {
//				color = float4(1, 1, 1, 0.0f);
//			}
//			else
//			{
//				color = float4(float3(scene->materials[index].albedo), 0.0f);
//			}
//		}
		out.write(color, gid);
	}
}
