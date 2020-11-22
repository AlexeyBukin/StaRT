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

constant const float pi = 3.14159265358979323846f;

typedef enum				s_shp_type
{
	SHP_NONE,
	SHP_PLANE,
	SHP_SPHERE,
	SHP_CYLINDER,
	SHP_CONE
//	SHP_MODEL
}							t_shp_type;

struct					s_sphere
{
	packed_float3		pos;
	float				r;
};

struct					s_plane
{
	packed_float3		n;
	float				d;
};

typedef union			u_gpu_shape
{
	struct s_sphere		sphere;
	struct s_plane		plane;
}						t_gpu_shape;

struct					s_cam
{
	int					id;
	packed_float3		pos;
	packed_float3		forward;
	packed_float3		up;
	packed_float3		right;
	packed_float2		fov;
};

struct					s_c_mat
{
	float 				metalness;
	float 				roughness;
	float 				ior;
	float 				transparency;
	packed_float3		albedo;
	packed_float3		f0;
};

typedef struct			s_material
{
	struct s_c_mat		c_mat;
	texture2d<float>	albedo_map;
}						t_material;

typedef struct			s_gpu_obj
{
	unsigned int		id;
	unsigned int		mat_index;
	packed_float3		map_axis_x;
	packed_float3		map_axis_y;
	packed_float3		map_axis_z;
	int					shape_type;
	t_gpu_shape			shape;
}						t_gpu_obj;

typedef struct			s_gpu_info
{
	size_t				obj_num;
	size_t				mat_num;
	size_t				txr_num;
	size_t				render_size;
	size_t				render_square_num;
	size_t				render_square_current;
	t_gpu_cam			camera;
}						t_gpu_info;

kernel void scene_test(		device struct		s_gpu_info	info		[[buffer(0)]],
							device struct		s_gpu_obj	*objects	[[buffer(1)]],
							device struct		s_material	*materials	[[buffer(2)]],
							texture2d<float,access::write> 	out			[[texture(3)]],
							uint2                  			gid			[[thread_position_in_grid]])
{
	uint2 size = uint2(out.get_width(), out.get_height());
	device struct s_cam *cam = &scene->camera;

	if (gid.x < size.x && gid.y < size.y)
	{
		float4 color = float4(0.5, 0.5, 0.5, 0);
		out.write(color, gid);
	}
}
