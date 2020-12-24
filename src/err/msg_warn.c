/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_warn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 04:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 04:52:27 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg		msg_warn(char *str)
{
	//TODO add debug verbose func
	//rt_debug(str);
	return ((t_msg){MSG_WARN, str});
}
