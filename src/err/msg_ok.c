/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_ok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:05:10 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 01:06:28 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg		msg_ok(char *str)
{
	return ((t_msg){MSG_OK, str});
}

/*
** msg_oks() used with static strings
** Because of server will free() every MSG_OK string
*/

t_msg		msg_oks(char *str)
{
	return ((t_msg){MSG_OK, ft_strdup(str)});
}
