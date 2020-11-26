#include "rt.h"

t_msg				cmd_swich_condition(t_rt *rt, t_parser parser,
	(t_msg)(*f)(t_rt*, t_parser*), char *str)
{
	if (rt == NULL || parser == NULL || str == NULL || f == NULL)
		return(msg_err("NULL pointer in cmd_swich_cond"));
	parser->cur += ft_strlen(str);
	return (f(rt, parser));
}