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

typedef struct			s_cam
{
	packed_float3		pos;
	packed_float3		local_x;
	packed_float3		local_y;
	packed_float3		local_z;
	packed_float2		fov;
}						t_gpu_cam;

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
	texture2d<float,access::read>	albedo_map [[id(0)]];
	struct s_c_mat					c_mat;
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
	unsigned			obj_num;
	unsigned			mat_num;
	unsigned			txr_num;
	unsigned			render_size;
	unsigned			render_square_num;
	unsigned			render_square_current;
	t_gpu_cam			camera;
}						t_gpu_info;

kernel void scene_test(		device struct		s_gpu_info	*info		[[buffer(0)]],
							device struct		s_gpu_obj	*objects	[[buffer(1)]],
							device struct		s_material	*materials	[[buffer(2)]],
							texture2d<float,access::write> 	out			[[texture(3)]],
							uint2                  			gid			[[thread_position_in_grid]])
{
	uint2 size = uint2(out.get_width(), out.get_height());

	device struct s_material *mat = &(materials[0]);
	if (mat == nullptr)
		return ;
	if (gid.x < size.x && gid.y < size.y)
	{
		float4 color = mat->albedo_map.read(gid);//[gid.y][gid.x];
		out.write(color, gid);
	}
}
