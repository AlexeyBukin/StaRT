//#include "rt.h"
//# define COUNT_COMMANDS	4
//# define COUNT_OBJECTS	4
//
///*
//**		checking if t_word w matching to
//**		anything in *check_array, if there is
//**		no match returns -1, else - index of
//**		equal element in array
//*/
//
//int			check_word(t_word w, t_word *check_array, int how_many_args)
//{
//	int		i;
//
//	i = 0;
//	while (i < how_many_args)
//	{
//		if (ft_strncmp(w.w_ptr, check_array[i].w_ptr, w.l) == 0 && w.l == check_array[i].l)
//			return (i);
//		i++;
//	}
//	return (-1);
//}
//
///*
//**		empty functions
//*/
//
//int			rm(t_rt *rt, t_word *w)
//{
//	(void)w;
//	(void)rt;
//	ft_putendl("rm");
//	return (0);
//}
//
//int			set(t_rt *rt, t_word *w)
//{
//	(void)w;
//	(void)rt;
//	ft_putendl("set");
//	return (0);
//}
//
//int			ls(t_rt *rt, t_word *w)
//{
//	(void)w;
//	(void)rt;
//	ft_putendl("ls");
//	return (0);
//}
//
///*
//**		norme is ok with statics;
//**		TODO: in future if anyone would like to add some
//**		functions in parser, "check" and "f" variables would
//**		need to be rewrite, and carefully - every word name
//**		should match to function соррян у меня плохо с грамматикой
//*/
//
//int 			validate_all_components(t_rt *rt, t_word *cmd_l)
//{
//	(void)rt;
//	static t_word	check[COUNT_COMMANDS] = {(t_word){"add", 3}, (t_word){"rm", 2},
//											(t_word){"set", 3}, (t_word){"ls", 2}};
//	static int 		(*f[COUNT_COMMANDS])() = {cmd_add, rm, set, ls};
//	int				function_index;
//
//	function_index = check_word(cmd_l[0], (t_word *)check, 4);
//	if (function_index == -1)
//	{
//		rt_err("validate_all_components(): command is invalid."
//			" Available commands: add, rm, set, ls.");
//		return(-1);
//	}
//	return (f[function_index](rt, cmd_l));
//}
