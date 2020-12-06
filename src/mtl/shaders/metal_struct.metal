#include <metal_stdlib>
using namespace metal;

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define ALPHA_MAX	255
# define COLOR_MAX	255
# define RT_MAX_OBJECTS 128
# define RT_MAX_MATERIALS 32
# define RT_MAX_LIGHTS 16
# define RT_MAX_CAMERAS 16

constant const float pi = 3.14159265358979323846f;


typedef packed_float4	t_color;

typedef enum			e_shape_type
{
	NONE = 0,
	CONE,
	SPHERE,
	PLANE,
	CYLINDER,
	TORUS
}						t_shape_type;

typedef enum			e_camera_projection
{
	PROJECTION_ORTOGRAPHIC,
	PROJECTION_PERSPECTIVE
}						t_projection;

typedef struct			Ray
{
	float3				pos;
	float3				dir;
	float				max;
	float				min;
	Ray() : pos(0.0f), dir(1.0f), max(INFINITY), min(0) {};
	Ray(	float3 p, float3 d,
	float max = INFINITY, float min = 0.0 )
	: pos(p), dir(normalize(d)), max(max), min(min) {};
} 						Ray;

typedef struct			s_mat3x3
{
	packed_float3		x;
	packed_float3		y;
	packed_float3		z;
}						t_mat3x3;

typedef struct			s_mat
{
	int					id;
	packed_float3		albedo;
	packed_float3		f0;
	float				transparency;
	float				ior;
	float 				roughness;
	float 				metalness;
}						t_m;

typedef struct			s_sphere
{
	packed_float3		center;
	float				r;
}						t_sphere;

typedef struct			s_cone
{
	packed_float3		head;
	packed_float3		tail;
	float				r;
}						t_cone;

typedef struct			s_plane
{
	float 				d;
	packed_float3		normal;
}						t_plane;



typedef struct			s_cylinder
{
	packed_float3		head;
	packed_float3		tail;
	float				r;
}						t_cylinder;


typedef struct			s_torus
{
	packed_float3		center;
	packed_float3		ins_vec;
	float 				R;
	float				r;
}						t_torus;

typedef union			u_shape
{
	struct s_sphere		sphere;
	struct s_cone		cone;
	struct s_plane		plane;
	struct s_cylinder	cylinder;
	struct s_torus		torus;
}						t_shape;

typedef struct			s_obj
{
	int 				id;
	int					material_id;
	t_mat3x3			map_axis;
	t_shape_type		type;
	t_shape				obj;
}						t_obj;

typedef	struct			s_light
{
	int 				id;
	packed_float3		pos;
	packed_float3		col;
	float				power;
}						t_light;

typedef struct			s_cam
{
	int					id;
	packed_float3		pos;
	t_mat3x3			rot_axis;
	packed_float2		fov;
}						t_cam;

typedef struct			s_info
{
	int					obj_num;
	int					mat_num;
	int					txr_num;
	int					cam_num;
	int 				light_num;
	int					sampling_num;
	int					render_size;
	int					render_square_num;
	int					render_square_current;
	struct s_cam		cameras[RT_MAX_CAMERAS];
	int					camera_active;
}						t_info;

typedef struct			s_gpu_scene
{
	device t_info		*info		[[id(0)]];
	device t_obj		*objects	[[id(1)]];
	device t_m			*materials	[[id(2)]];
	device t_light		*lights		[[id(3)]];
}						t_scn;

typedef struct					s_gpu_texture
{
	texture2d<float,access::read> texture [[id(0)]];
//	texture2d<float,access::read> texture1 [[id(1)]];
}								t_gpu_texture;

typedef struct			s_ggx_loop
{
	Ray					normal;
	Ray					cam_ray;
	int					light_id;
	int 				mat_id;
}						t_ggx_loop;
