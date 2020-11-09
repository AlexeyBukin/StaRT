//
// Created by Hugor Chau on 11/8/20.
//

#include "rt.h"
# define COUNT_COMMANDS	6
# define COUNT_OBJECTS	6

/*
**		word[0] was parsed;
**		next commands: validate
*/

// int		read_vec(char **source, t_vec3 *res)
// {
// 	char		*text;

// 	if (source == NULL || res == NULL)
// 		return (ft_puterror(1, "Entered NULL pointers"));
// 	if ((text = *source) == NULL)
// 		return (ft_puterror(2, "Entered NULL pointers"));
// 	if (*text != '<')
// 		return (ft_puterror(3, "Syntax error: Expected \'<\'"));
// 	text++;
// 	res->x = read_num(&text);
// 	if (read_comma(&text) < 0)
// 		return (ft_puterror(4, "Syntax error: Expected \',\'"));
// 	res->y = read_num(&text);
// 	if (read_comma(&text) < 0)
// 		return (ft_puterror(5, "Syntax error: Expected \',\'"));
// 	res->z = read_num(&text);
// 	if (*text != '>')
// 		return (ft_puterror(6, "Syntax error: Expected \'>\'"));
// 	text++;
// 	if (vec_is_inf(*res))
// 		return (ft_puterror(7, "Parse error: vector is infinite"));
// 	*source = text;
// 	return (0);
// }

int			cmd_parse_obj(t_rt *rt, t_word *w)
{
	// (void)w;
	(void)rt;
	ft_putstr("object is valid: ");
	ft_putendl(w[1].w_ptr);
	// t_vec3		pos = parse_pos()
	// scn_add_sphere(rt->scene, )
	return (0);
}

int			find_flag(t_word *w, char *flag)
{
	int 	i;

	i = 0;
	while (i < MAX_PARAMS)
	{
		if (w[i].l != 0)
		{
			if (ft_strncmp(w[i].w_ptr, flag, ft_strlen(flag)) == 0)
				return (i);
		}
		i++;
	}
	return (0);
}

t_vec3		parse_pos(t_word *w)
{
	t_vec3	pos;
	int		word_nbr;

	pos = (t_vec3){0.0, 0.0, 0.0};
	word_nbr = find_flag(w, "-p");
	if (word_nbr != 0)
	{
		pos = (t_vec3){1.0, 1.0, 1.0};
		// read_vec(&(w[word_nbr].w_ptr + 2), &pos);
	}
	return(pos);
}

float		parse_rad(t_word *w)
{
	float	rad;
	int		word_nbr;

	rad = 0.1;
	word_nbr = find_flag(w, "-r");
	if (word_nbr != 0)
	{
		rad = ft_atof(w[word_nbr].w_ptr + 2);
	}
	return (rad);
}

uint		parse_mat(t_word *w, t_rt *rt)
{
	(void)rt;
	uint	mat;
	int		word_nbr;

	mat = 1;//TODO: Set default material id here
	word_nbr = find_flag(w, "-m");
	if (word_nbr != 0)
	{
		mat = 777;//TODO: parse material here
	}
	return (mat);
}

int			cmd_parse_sphere(t_rt *rt, t_word *w)//TODO: catch segfault...
{
	// (void)rt;
	ft_putstr("object is valid: ");
	ft_putendl(w[1].w_ptr);
	t_vec3		pos = parse_pos(w);
	float		rad = parse_rad(w);
	uint		mat = parse_mat(w, rt);
	scn_add_sphere(rt->scene, pos, rad, mat);
	return (0);
}

//int		scn_add_sphere(t_scn *scn, t_vec3 pos, float r, uint mid)

//int		scn_add_material(t_scn *scn, t_vec3[] arr_w_vecs, t_scal[] arr_w_scals)

/*
**		norme is ok with statics;
**		TODO: replace cmd_parse_obj with real functions, like
**		cmd_parse_sphere, cmd_parse_cone, cmd_parse_plane,
**		cmd_parse_camera, cmd_parse_material;
**		TODO: in future if anyone would like to add some
**		types to parser, "check" and "f" variables would
**		need to be rewrite, and carefully - every word name
**		should match to function
*/

int			cmd_add(t_rt *rt, t_word *w)
{
	static t_word	check[COUNT_COMMANDS] = {(t_word){"sphere", 6}, (t_word){"cone", 4},
								(t_word){"cylinder", 8}, (t_word){"plane", 5},
								(t_word){"camera", 6}, (t_word){"material", 8}};
	static int		(*f[6])() = {cmd_parse_sphere, cmd_parse_obj,
								cmd_parse_obj, cmd_parse_obj,
								cmd_parse_obj, cmd_parse_obj};//replace with coms exit, shutdown, add, etc.
	int							function_index;

	(void)w;
	(void)rt;
	ft_putendl("add");
	function_index = check_word(w[1], (t_word *)check, 6);
	if (function_index == -1)
	{
		rt_err("validate_all_components(): cmd_add(): object is invalid."
			" Available objects: sphere, cone, cylinder, plane, camera, material.");
		return(-1);

	}
	f[check_word(w[1], (t_word *)check, 6)](rt, w);
	return (0);
}
