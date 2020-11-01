/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/01 17:13:15 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRV_H
# define SRV_H

# include "srv_types.h"
# include "rts.h"

# define MSG_NONE   0
# define MSG_OK     1
# define MSG_ACTIVE 2
# define MSG_EXIT   3
# define MSG_ERROR -1

int					srv_init(t_rt *rt);
int					srv_exit(t_rt *rt);
void*				srv_loop(void* rt_pointer);
int					srv_request(t_rt *rt, char *str);
int					srv_parse_str(const char* request, char **response);
int					msleep(long msec);
int					srv_ext_client_process(t_rt *rt);

#endif
