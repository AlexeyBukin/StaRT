/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 02:49:57 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg					cmd_ls_scene(t_rt *rt, char *source)
{
	(void)rt;
	(void)source;
	return (msg_ok("This is ls scene"));
}

t_msg					cmd_ls_sphere(t_rt *rt, char *source)
{
	(void)rt;
	(void)source;
	return (msg_ok("This is ls sphere"));
}
