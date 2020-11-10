/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_shutdown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:25:43 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Must be run from gtk thread only!
*/

int		srv_shutdown(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	return (srv_request(rt, "shutdown"));
}
