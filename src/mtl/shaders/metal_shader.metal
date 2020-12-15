/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    metal_shader.metal                                 :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2020/09/11 18:30:35 by wpoudre           #+#    #+#              */
/*    Updated: 2020/09/11 18:30:37 by wpoudre          ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include <metal_stdlib>
using namespace metal;

//float mabs(float x){ return (x < 0)? -x : x; }
//
//float roott(float num, int rootDegree) {
//	float eps = 0.01;
//	float root = num / rootDegree;
//	float rn = num;
//	while(mabs(root - rn) >= eps)
//	{
//		rn = num;
//		for (int i = 1; i < rootDegree; i++)
//		{
//			rn = rn / root;
//		}
//		root = 0.5 * (rn + root);
//	}
//	return (root);
//}

//float 		root(float num)
//{
//	float	r;
//	float	q;
//	int		i;
//
//	q = 0;
//	r = 1;
//	i = 0;
//	if (num == 0.0)
//		return 0;
//	for (int i = 0; i < 15; i++)
//	{
//		q = 1 / pow(10.0, i);
//		while (((r+q) * (r+q) * (r+q)) < num)
//			r += q;
//	}
//	return r;
//}

float rand(int x, int y, int z)
{
	int seed = x + y * 57 + z * 241;
	seed= (seed<< 13) ^ seed;
	return (( 1.0 - ( (seed * (seed * seed * 15731 + 789221) + 1376312589) & 2147483647) / 1073741824.0f) + 1.0f) / 2.0f;
}

bool		vec_point_is_behind(float3 vec_from_zero, float3 point)
{
	float3 res;

	res = vec_from_zero * point;
	if (res.x + res.y + res.z < 0)
		return (true);
	return (false);
}

bool		ray_point_is_behind(Ray ray, float3 point)
{
	return (vec_point_is_behind(ray.dir, (point - ray.pos)));
}

float					num_clamp(float val, float min, float max)
{
	if (val < min)
	{
		return (min);
	}
	if (val > max)
	{
		return (max);
	}
	return (val);
}

float3			vec_clamp(float3 source, float min, float max)
{
	source.x = num_clamp(source.x, min, max);
	source.y = num_clamp(source.y, min, max);
	source.z = num_clamp(source.z, min, max);
	return (source);
}

float4			color_clamp(float4 source, float min, float max)
{
	source.x = num_clamp(source.x, min, max);
	source.y = num_clamp(source.y, min, max);
	source.z = num_clamp(source.z, min, max);
	source.w = num_clamp(source.w, min, max);
	return (source);
}

float3		vec_to_srgb(float3 v)
{
	v.x = pow(v.x, 1.0f / 2.2f);
	v.y = pow(v.y, 1.0f / 2.2f);
	v.z = pow(v.z, 1.0f / 2.2f);
	return (v);
}

float4 	col_from_vec(float3 vector)
{
	float4 res;

	res[0] = vector.x;
	res[1] = vector.y;
	res[2] = vector.z;
	res[3] = ALPHA_MAX;
	return (res);
}

float4		col_from_normal(float3 vector)
{
	float4	res;

	vector = normalize(vector);
	res.x = (unsigned char)(vector.x + 1) * COLOR_MAX / 2;
	res.y = (unsigned char)(vector.y + 1) * COLOR_MAX / 2;
	res.z = (unsigned char)(vector.z + 1) * COLOR_MAX / 2;
	res.w = ALPHA_MAX;
	return (res);

}

//float4		col_from_vec_norm(float3 vector)
//{
//	float4	res;
//
//	res.x = (float)(num_clamp(vector.x, 0, 1));
//	res.y = (float)(num_clamp(vector.y, 0, 1));
//	res.z = (float)(num_clamp(vector.z, 0, 1));
//	res.w = 0;
//	return (res);
//}

float4		col_from_vec_norm(float3 vector)
{
	float4	res;

	res.x = num_clamp(vector.x, 0, 1);
	res.y = num_clamp(vector.y, 0, 1);
	res.z = num_clamp(vector.z, 0, 1);
	res.w = 1;
	return (res);
}

float		ggx_distribution(float cos_theta_nh, float alpha)
{
	float		alpha2;
	float		nh_sqr;
	float		den;

	alpha2 = alpha * alpha;
	nh_sqr = num_clamp(pow(cos_theta_nh, 2), 0, 1);
	den = nh_sqr * alpha2 + (1.0 - nh_sqr);
	return (alpha2 / (pi * den * den));
}

float		ggx_partial_geometry(float cos_theta_n, float alpha)
{
	cos_theta_n = num_clamp(pow(cos_theta_n, 2), 0, 1);
	cos_theta_n = (1 - cos_theta_n) / cos_theta_n;
	return (2.0 / (1.0 + sqrt(1.0 + alpha * alpha * cos_theta_n)));
}

float3	fresnel_schlick(float3 f0, float cos_theta)
{
	float3	res;

	cos_theta = 1.0 - num_clamp(cos_theta, 0.0, 1.0);
	cos_theta = cos_theta * cos_theta * cos_theta * cos_theta * cos_theta;
	res = (float3(1.0) - f0) * cos_theta;
	res = f0 + res;
	return (res);
}

float					trace_dot_plane(Ray ray, device t_obj *fig)
{
	struct	s_plane		pl[1];
	float				d_dot_v;

	if (!fig)
		return (INFINITY);
	pl[0] = fig->obj.plane;
//	ray.dir = normalize(ray.dir);
	d_dot_v = dot(ray.dir, float3(pl->normal));
	return (-1 * dot((ray.pos - (float3(pl->normal) * (-1.0 * pl->d))),
				  float3(pl->normal)) / d_dot_v);
}

float					trace_dot_pl(Ray ray, t_plane pl)
{
	float				d_dot_v;

//	ray.dir = normalize(ray.dir);
	d_dot_v = dot(ray.dir, float3(pl.normal));
	return (-1 * dot((ray.pos - (float3(pl.normal) * (-1.0 * pl.d))),
				  float3(pl.normal)) / d_dot_v);
}


float					trace_dot_cap(Ray ray, Ray plane_ray)
{
	thread t_obj		fig;

	fig.type = PLANE;
	fig.obj.plane.normal = plane_ray.dir;
	fig.obj.plane.d = (dot(plane_ray.dir, plane_ray.pos));
//	fig.obj.plane.d = -1 * (dot(plane_ray.dir, plane_ray.pos));
	return (trace_dot_pl(ray, fig.obj.plane));
}

static float2			sphere_intersect_points(Ray ray, device t_sphere *sphere)
{
	float		a;
	float		b;
	float		c;
	float		d;
	float3		a_min_c;

	a_min_c = (ray.pos - float3(sphere->center));
	a = dot(ray.dir, ray.dir);
	b = 2 * dot(ray.dir, a_min_c);
	c = dot(a_min_c, a_min_c) - (sphere->r * sphere->r);
	d = pow(b, 2) - 4 * a * c;
	if (d >= 0)
		return (float2((-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a)));
	return (float2(INFINITY));
}

float					trace_dot_sphere(Ray ray, device t_obj *fig)
{
	float			minimal;
	float2			points;

	if (!fig)
		return (INFINITY);
	points = sphere_intersect_points(ray, &fig->obj.sphere);
	minimal = INFINITY;
	if (points.x > 0 && points.x < minimal)
		minimal = points.x;
	if (points.y > 0 && points.y < minimal)
		minimal = points.y;
	return (minimal);
}

///cone trace------------------------------------------------------

float3					cone_intersect(Ray ray, device struct s_cone *cone, float3 v)
{
	float3		x;
	float		a;
	float		b;
	float		c;
	float		d;

	d = cone->r / length(float3(cone->tail) - float3(cone->head));
	x = ray.pos - float3(cone->tail);
	a = dot(ray.dir, ray.dir) - (1 + (d * d)) * pow(dot(ray.dir, v), 2);
	b = (dot(ray.dir, x) - dot(ray.dir, v) * (1 + d * d) * dot(x, v)) * 2;
	c = dot(x, x) - (1 + d * d) * pow(dot(x, v), 2);
	d = (b * b) - 4 * a * c;
	if (d < 0)
		return (float3(INFINITY));
	d = sqrt(d);
	return (float3((-b - d) / (2 * a), (-b + d) / (2 * a), 0));
}

static float3			cone_capped(Ray ray_in, device struct s_cone *cone)
{
	float3				points;
	float3				v;
	float3				m;
	float3				clamped;
	float				x_dot_v;

	v = normalize(float3(cone->tail) - float3(cone->head));
	ray_in.dir = normalize(ray_in.dir);
	points = cone_intersect(ray_in, cone, v);
	x_dot_v = dot(ray_in.pos - float3(cone->head), v);
	m.x = dot(ray_in.dir, v * points.x) + x_dot_v;
	m.y = dot(ray_in.dir, v * points.y) + x_dot_v;
	clamped.x = num_clamp(m.x, 0, length(float3(cone->head) - float3(cone->tail)));
	clamped.y = num_clamp(m.y, 0, length(float3(cone->head) - float3(cone->tail)));
	if (clamped.x != m.x && clamped.y != m.y)
		return (float3(INFINITY));
	if (clamped.x != m.x)
		points.x = trace_dot_cap(ray_in, Ray(float3(cone->tail), v));
	if (clamped.y != m.y)
		points.y = trace_dot_cap(ray_in, Ray(float3(cone->tail), v));
	return (points);
}

float					trace_dot_cone(Ray ray, device t_obj *fig)
{
	float 				minimal;
	float3 				points;

	if (!fig)
		return (INFINITY);
	points = cone_capped(ray, &(fig->obj.cone));
	minimal = INFINITY;
	if (points.x > 0 && points.x < minimal)
		minimal = points.x;
	if (points.y > 0 && points.y < minimal)
		minimal = points.y;
	return (minimal);
}

///cylinder trace-----------------------------------------------

float3					cylinder_intersect(Ray ray, struct s_cylinder cyl, float3 v)
{
	float3				x;
	float				a;
	float				b;
	float				c;
	float				d;

	x = float3(ray.pos) - float3(cyl.tail);
	a = dot(ray.dir, ray.dir) - pow(dot(ray.dir, v), 2);
	b = (dot(ray.dir, x) - (dot(ray.dir, v) * dot(x, v))) * 2;
	c = dot(x, x) - pow(dot(x, v), 2) - pow(cyl.r, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (float3(INFINITY));
	d = sqrt(d);
	return (float3((-b - d) / (2 * a), (-b + d) / (2 * a), 0));
}

static float3			cylinder_capped(Ray ray, struct s_cylinder cyl)
{
	float				maxm;
	float3				points;
	float3				v;
	float3				m;
	float				x_dot_v;

	v = normalize(float3(cyl.head) - float3(cyl.tail));
	points = cylinder_intersect(ray, cyl, v);
	maxm = length(float3(cyl.tail) - float3(cyl.head));
	x_dot_v = dot((ray.pos - float3(cyl.tail)), v);
	m.x = dot(ray.dir, (v * points.x)) + x_dot_v;
	m.y = dot(ray.dir, (v * points.y)) + x_dot_v;
	if (points.x != INFINITY)
	{
		if (m.x >= 0 && m.x <= maxm && m.y >= 0 && m.y <= maxm)
			return (points);
	}
	if ((m.x < 0 && m.y < 0) || (m.x > maxm && m.y > maxm))
		return (float3(INFINITY));
	if (m.x < 0)
		points.x = trace_dot_cap(ray, Ray(float3(cyl.tail), (-1 * v)));
	if (m.y < 0)
		points.y = trace_dot_cap(ray, Ray(float3(cyl.tail), (-1 * v)));
	if (m.x > maxm)
		points.x = trace_dot_cap(ray, Ray(float3(cyl.head), v));
	if (m.y > maxm)
		points.y = trace_dot_cap(ray, Ray(float3(cyl.head), v));
	return (points);
}

float					trace_dot_cylinder(Ray ray, device t_obj *fig)
{
	float				minimal;
	float3				points;

	if (!fig)
		return (INFINITY);
	points = cylinder_capped(ray, fig->obj.cylinder);
	minimal = INFINITY;
	if (points.x > 0 && points.x < minimal)
		minimal = points.x;
	if (points.y > 0 && points.y < minimal)
		minimal = points.y;
	return (minimal);
}

float4 SolveQuartic(float A, float B, float C, float D, float E)
{
	float4 res;
	float alpha = -((3 * pow(B, 2.0f)) / (8 * pow(A, 2.0f))) + (C / A);
	float beta = (pow(B, 3) / (8 * pow(A, 3))) - ((B * C) / (2 * pow(A, 2))) + (D / A);
	float gama = -((3 * pow(B, 4)) / (256 * pow(A, 4))) + ((C * pow(B, 2)) / (16 * pow(A, 3))) - ((B * D) / (4 * pow(A, 2))) + (E / A);
	if (beta == 0.0)
	{
		res[0] = -(B / (4 * A)) + sqrt((-alpha + sqrt(pow(alpha, 2) - 4 * gama)) / 2);
		res[1] = -(B / (4 * A)) + sqrt((-alpha - sqrt(pow(alpha, 2) - 4 * gama)) / 2);
		res[2] = -(B / (4 * A)) - sqrt((-alpha + sqrt(pow(alpha, 2) - 4 * gama)) / 2);
		res[3] = -(B / (4 * A)) - sqrt((-alpha - sqrt(pow(alpha, 2) - 4 * gama)) / 2);
		return (res);
	}
	float p = -(pow(alpha, 2) / 12) - gama;
	float q = -(pow(alpha, 3) / 108) + (alpha * gama / 3) - (pow(beta, 2) / 8);
	float r = -(q / 2) + (sqrt((pow(q, 2) / 4) + (pow(p, 3) / 27)));
	float u = pow(r, 1.0f / 3.0f);
	float y;
	if (u == 0.0)
		y = - (5 / 6 * alpha) - pow(q, 1.0f / 3.0f);
	else
		y = - (5 / 6 * alpha) + u - (p / (3 * u));
	float w = sqrt(alpha + 2 * y);
	res[0] = -(B / 4 * A) + ((w + sqrt(-(3 * alpha + 2 * y + (2 * beta)/w))) / 2);
	res[1] = -(B / 4 * A) + ((w - sqrt(-(3 * alpha + 2 * y + (2 * beta)/w))) / 2);
	res[2] = -(B / 4 * A) + (-(w + sqrt(-(3 * alpha + 2 * y - (2 * beta)/w))) / 2);
	res[3] = -(B / 4 * A) + (-(w - sqrt(-(3 * alpha + 2 * y - (2 * beta)/w))) / 2);
	return (res);
}

//float4		fourth_degree_equation(float a, float b, float c, float d, float e)
//{
//	float4	res;
//	float 	p;
//	float 	q;
//	float 	S;
//	float 	Q;
//	float 	delta;
//	float 	delta0;
//	float	delta1;
//
//	delta =	256 * pow(a, 3) * pow(e, 3) - 192 * pow(a, 2) * b * d * pow(e, 2) -
//			128 * pow(a, 2) * pow(c, 2) * pow(e, 2) + 144 * pow(a, 2) * c *
//			pow(d, 2) * e -	27 * pow(a, 2) * pow(d, 4) + 144 * a * pow(b, 2) *
//			c * pow(e, 2) - 6 * a * pow(b, 2) *	pow(d, 2) * e - 80 * a * b *
//			pow(c, 2) * d * e + 18 * a * b * c * pow(d, 3) + 16 * a *
//			pow(c, 4) * e - 4 * a * pow(c, 3) * pow(d, 2) - 27 * pow(b, 4) *
//			pow(e, 2) + 18 * pow(b, 3) * c * d * e - 4 * pow(b, 3) *
//			pow(d, 3) -	4 * pow(b, 2) * pow(c, 3) * e +	pow(b, 2) * pow(c, 2) +
//			pow(d, 2);
//	p = (8 * a * c - 3 * b * b) / (8 * a * a);
//	q = (b * b * b - 4 * a * b * c + 8 * a * a * d) / (8 * a * a * a);
//	delta0 = c * c - 3 * b * d + 12 * a * e;
//	delta1 = 2 * c * c * c - 9 * b * c * d + 27 * b * b * e + 27 * a * d * d - 72 * a * c * e;
//	Q = pow(((delta1 + sqrt(pow(delta1, 2) - 4 * pow(delta0, 3))) / 2), (1.0 / 3.0));
////	Q = pow(((delta1 + sqrt(-27 * delta)) / 2), (1.0 / 3.0));
//	float fi = acos(delta1 / ( 2 * sqrt(pow(delta0, 2))));
//	if (delta <= 0)
//		S = 1 / 2 * sqrt(-1 * (2/3 * p) + 1 / (3 * a) * (Q + delta0 / Q));
//	else
//		S = 1 / 2 * (sqrt(- 2 / 3 * p + 2 / 3 * a * sqrt(delta0) * cos(fi / 3)));
//	res.x = (-b / 4 * a) - S + (0.5 * sqrt(-4 * pow(S, 2) - 2 * p + q / S));
//	res.y = (-b / 4 * a) - S - (0.5 * sqrt(-4 * pow(S, 2) - 2 * p + q / S));
//	res.z = (-b / 4 * a) + S + (0.5 * sqrt(-4 * pow(S, 2) - 2 * p + q / S));
//	res.w = (-b / 4 * a) + S - (0.5 * sqrt(-4 * pow(S, 2) - 2 * p + q / S));
//	return (res);
//}

float4		finding_the_multipliers(Ray ray, device t_obj *fig, float3 x)
{
	float	m = dot(ray.dir, ray.dir);
	float	n = dot(ray.dir, x);
	float	o = dot(x, x);
	float	p = dot(ray.dir, float3(fig->obj.torus.ins_vec));
	float	q = dot(x, float3(fig->obj.torus.ins_vec));
	float 	a = pow(m, 2);
	float	b = 4 * m * n;
	float 	c = 4 * pow(m, 2) + 2 * m * o - 2 * (pow(fig->obj.torus.R, 2) +
			pow(fig->obj.torus.r, 2)) * m + 4 * pow(fig->obj.torus.R, 2) *
			pow(p, 2);
	float	d = 4 * n * o - 4 * (pow(fig->obj.torus.R, 2) +
			pow(fig->obj.torus.r, 2)) * n + 8 * pow(fig->obj.torus.R, 2)
			* p * q;
	float	e = pow(o, 2) - 2 * (pow(fig->obj.torus.R, 2) +
			pow(fig->obj.torus.r, 2)) * o + 4 * pow(fig->obj.torus.R, 2) *
			pow(q, 2) + pow(pow(fig->obj.torus.R, 2) -
			pow(fig->obj.torus.r, 2), 2);
	return (SolveQuartic(a, b, c, d, e));
}

float 		trace_dot_torus(Ray ray, device t_obj *fig)
{
	float3	x;
	float4	points;

	x = ray.pos - float3(fig->obj.torus.center);
	points = finding_the_multipliers(ray, fig, x);
	float minimal = INFINITY;
	if (points.x > 0 && points.x < minimal)
		minimal = points.x;
	if (points.y > 0 && points.y < minimal)
		minimal = points.y;
	if (points.z > 0 && points.z < minimal)
		minimal = points.z;
	if (points.w > 0 && points.w < minimal)
		minimal = points.w;
	return (minimal);
}

///figur trace-------------------------------------------------

float					trace_dot_fig(Ray ray, device t_obj *fig)
{
	if (!fig)
		return (INFINITY);
	if (fig->type == PLANE)
		return (trace_dot_plane(ray, fig));
	else if (fig->type == SPHERE)
		return (trace_dot_sphere(ray, fig));
	else if (fig->type == CONE)
		return (trace_dot_cone(ray, fig));
	else if (fig->type == CYLINDER)
		return (trace_dot_cylinder(ray, fig));
	else if (fig->type == TORUS)
		return (trace_dot_torus(ray, fig));
	else
		return (INFINITY);
}

int			rt_trace_nearest_dist(device t_scn *scene, Ray ray, thread float &dist, thread t_obj &nearest)
{
	float				tmp_dist;
	float				res_dist;
	int 				i;
	int					nearest_num;
	t_obj 				near;

	near = nearest;
//	if (!scene)
//		return (0);
	res_dist = INFINITY;
	i = 0;
	while (i < scene->info->obj_num)
	{
		if (near.id != scene->objects[i].id)
		{
			tmp_dist = trace_dot_fig(ray, &(scene->objects[i]));
			if (tmp_dist < res_dist && tmp_dist > 0)
			{
				res_dist = tmp_dist;
				nearest = scene->objects[i];
				nearest_num = i;
			}
		}
		i++;
	}
	dist = res_dist;
	return (nearest_num);
}

float		brdf_get_d(float3 n, float3 v, float3 l, device struct s_mat_pbr *mat)
{
	float	d;
	float	roug_sqr;
	float3	h;

//	if (!mat)
//		return (INFINITY);
	h = normalize(v + l);
	roug_sqr = pow(mat->roughness, 2);
	d = ggx_distribution(dot(n, h), roug_sqr);
	return (d);
}

float		brdf_get_g(float3 n, float3 v, float3 l, device struct s_mat_pbr *mat)
{
	float	g;
	float	roug_sqr;

//	if (!mat)
//		return (INFINITY);
	roug_sqr = pow(mat->roughness, 2);
	g = ggx_partial_geometry(dot(n, v), roug_sqr);
	g = g * ggx_partial_geometry(dot(n, l), roug_sqr);
	return (g);
}

///figur norm--------------------------------------------------

///plane norm--------------------------------------------------

float3				trace_normal_plane(Ray ray, device t_obj *fig)
{
	if (!fig)
		return (float3(INFINITY));
	if ((float)fig->obj.plane.normal.x * ray.pos.x + (float)fig->obj.plane.normal.y * ray.pos.y
		+ (float)fig->obj.plane.normal.z * ray.pos.z + (float)fig->obj.plane.d < 0)
		return (-(fig->obj.plane.normal));
	return (fig->obj.plane.normal);
}

///sphere norm-------------------------------------------------

float3				trace_normal_sphere(Ray ray, device t_obj *fig)
{
	float3				bounce_pos;

	if (!fig)
		return (float3(INFINITY));
	bounce_pos = ray.pos + (ray.dir * trace_dot_sphere(ray, fig));
	return (normalize(bounce_pos - float3(fig->obj.sphere.center)));
}

///cone norm---------------------------------------------------

float3				trace_normal_cone(Ray ray_in, device t_obj *fig)
{
	float3			v;
	float3			point_p;
	float3			ca;
	float			cg;
	float			cr;

	if (!fig)
		return (float3(INFINITY));
	v = float3(fig->obj.cone.head) - float3(fig->obj.cone.tail);
	ray_in.dir = normalize(ray_in.dir);
	point_p = ray_in.pos + ray_in.dir * trace_dot_cone(ray_in, fig);
	cg = length(v);
	cr = sqrt(pow(fig->obj.cone.r, 2) + pow(cg, 2));
	ca = normalize(v) * (cg * length(point_p - float3(fig->obj.cone.tail)) / cr);
	return (normalize(point_p - (float3(fig->obj.cone.tail) + ca)));
}

///cylinder norm-----------------------------------------------

static float3		cylinder_side_nrm(float3 p, float3 c, float3 v, float m)
{
	p = p - c;
	p = p - v * m;
	return (p);
}

static float3		cylinder_m(Ray ray, float3 v, float3 cyl_pos, float3 points)
{
	float			x_dot_v;
	float3			m;

	x_dot_v = dot(ray.pos - cyl_pos, v);
	m.x = dot(ray.dir, v * points.x) + x_dot_v;
	m.y = dot(ray.dir, v * points.y) + x_dot_v;
	return (m);
}

float3				trace_normal_cylinder(Ray ray, device t_obj *fig)
{
	float			maxm;
	float3			dis;
	float3			v;
	float3			m;
	float3			p;

	if (!fig)
		return (float3(INFINITY));
	v = normalize(float3(fig->obj.cylinder.head) - float3(fig->obj.cylinder.tail));
	dis = cylinder_intersect(ray, fig->obj.cylinder, v);
	maxm = length(float3(fig->obj.cylinder.tail) - float3(fig->obj.cylinder.head));
	m = cylinder_m(ray, v, float3(fig->obj.cylinder.tail), dis);
	if (dis.x > dis.y)
	{
		dis.x = dis.y;
		m.x = m.y;
	}
	if (m.x < 0)
		return (-(v));
	else if (m.x > maxm)
		return (v);
	p = ray.pos + ray.dir * dis.x;
	return (cylinder_side_nrm(p, float3(fig->obj.cylinder.tail), v, m.x));
}

///torus norm--------------------------------------------------

float3		trace_normal_torus(Ray ray, device t_obj *fig, float dist)
{
	float3	a;
	float3	n;
	float3	p;
	float	m;
	float	k;

	p = dist * (ray.pos + ray.dir);
	k = dot(p - float3(fig->obj.torus.center), float3(fig->obj.torus.ins_vec));
	a = p - float3(fig->obj.torus.ins_vec) * k;
	m = sqrt(pow(fig->obj.torus.r, 2) - pow(k, 2));
	n = p - a - (float3(fig->obj.torus.center) - a) * m / (fig->obj.torus.R + m);
	return (normalize(n));
}

float3		trace_normal_fig(Ray ray, device t_obj *fig, float dist)
{
	if (!fig)
		return (float3(INFINITY));
	if (fig->type == PLANE)
		return (trace_normal_plane(ray, fig));
	else if (fig->type == SPHERE)
		return (trace_normal_sphere(ray, fig));
	else if (fig->type == CONE)
		return (trace_normal_cone(ray, fig));
	else if (fig->type == CYLINDER)
		return (trace_normal_cylinder(ray, fig));
	else if (fig->type == TORUS)
		return (trace_normal_torus(ray, fig, dist));
	else
		return (float3(INFINITY));
}

float3 rerp(float val, float3 from, float3 to)
{
	return (normalize(from * cos(val) + to * sin(val)));
}

float3 rerp2(float2 val, float3 fromX, float3 toY, float3 toZ)
{
	return (normalize(rerp(val.x, fromX, toY) + rerp(val.y, fromX, toZ)));
}

float		map(float x, float2 in, float2 out)
{
	return ((x - in.x) * (out.y - out.x) / (in.y - in.x) + out.x);
}

float2		map2(float2 val, float4 in, float4 out)
{
	return (float2(map(val.x, in.xy, out.xy), map(val.y, in.zw, out.zw)));
}

float2		angle2_to_radians(float2 degrees)
{
	return (degrees * pi / 180.0f);
}

float4 colors_mix(float4 c1, float cof1, float4 c2, float cof2)
{
	return (color_clamp(c1 * cof1 + c2 * cof2, 0, 1));
}

//TODO reflections

//void reflections()
//


//float3 get_obj_center(device t_obj *fig)
//{
//	else if (fig->type == SPHERE)
//		return (fig->obj.sphere.center);
//	else if (fig->type == CONE)
//		return (float3(fig->obj.cone.head) - float3(fig->obj.cone.tail));
//	else if (fig->type == CYLINDER)
//		return (float3(fig->obj.cylinder.head) - float3(fig->obj.cylinder.tail));
//	else if (fig->type == TORUS)
//		return (fig->obj.torus.center);
//}
//
//float4 get_map_point(/*(pixel_map)*/,device t_scn *scene, float3 point, device t_obj *obj)
//{
//
//}

//Ray rt_camera_get_ray(device struct s_cam *cam, uint2 viewport, uint2 pixel)
//{
//	float2 v = static_cast<float2>(viewport);
//	float2 p = static_cast<float2>(pixel);
////	fov-range x and y
//	float4 fr;
//	fr.xy = float2(-1 * cam->fov[0] / 2, cam->fov[0] / 2);
//	fr.zw = float2(-1 * cam->fov[1] / 2, cam->fov[1] / 2);
////	fr.zw = float2(cam->fov[1] / 2, -1 * cam->fov[1] / 2);
////	map to radians m
//	p = map2(p, float4(0, v.x - 1, 0, v.y - 1), fr);
//	p = angle2_to_radians(p);
////	float3 dest = rerp2(p, float3(cam->forward), float3(cam->right), float3(cam->up));
//	float3 dest = rerp2(p, float3(cam->forward), float3(cam->up), float3(cam->right));
//	Ray ray = Ray(float3(cam->pos), dest);
//	return ray;
//}
