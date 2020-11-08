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

int			cmd_parse_obj(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	ft_putstr("object is valid: ");
	ft_putendl(w[1].w_ptr);
	return (0);
}

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
	static int		(*f[6])() = {cmd_parse_obj, cmd_parse_obj,
								cmd_parse_obj, cmd_parse_obj,
								cmd_parse_obj, cmd_parse_obj};
	int							function_index;

	(void)w;
	(void)rt;
	ft_putendl("add");
	function_index = check_word(w[1], (t_word *)check, 6);
	if (function_index == -1)
		rt_err("validate_all_components(): cmd_add(): object is invalid."
			" Available objects: sphere, cone, cylinder, plane, camera, material.");
	f[check_word(w[1], (t_word *)check, 6)](rt, w);
	return (0);
}
