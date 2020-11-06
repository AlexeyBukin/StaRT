#include "rt.h"

int			check_cmd(t_word w)
{
	if (ft_strncmp(w.w_ptr, "add", w.l) == 0)
		return (1);
//	(void)w;
	return (0);
}

int			add(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	return (0);
}

int			rm(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	return (0);
}

int			set(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	return (0);
}

int			ls(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	return (0);
}

int			error(t_rt *rt, t_word *w)
{
	(void)w;
	(void)rt;
	//TODO error print wrong arg
	return (-1);
}

int 			valid_cycle(t_rt *rt, t_word *cmd_l)
{
	(void)rt;
	static int 		(*f[5])(t_rt*, t_word*) = {error, add, rm, set, ls};

	return (f[check_cmd(cmd_l[0])](rt, cmd_l));

	return(0);
}
