/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:47:19 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/01 16:47:19 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRV_TYPES_H
# define SRV_TYPES_H

typedef struct		s_msg
{
	int				status;
	char			*str;
}					t_msg;

/*
** only server can write to response
*/

typedef struct		s_srv
{
	t_msg			response;
	t_msg			request;
}					t_srv;

#endif
