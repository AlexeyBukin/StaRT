/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 04:52:55 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRV_H
# define SRV_H

# include "srv_types.h"
# include "rt_types.h"

# define MSG_NONE   0
# define MSG_OK     1
# define MSG_WARN   2
# define MSG_EXIT   3
# define MSG_SHUT   4
# define MSG_ERROR -1

# define SRV_HELLO "Server is ready. Type 'exit' to close connection.\n"
# define SRV_BUSY  "Server is currently used by another session/user. Try later.\n"
# define SRV_ERR   "Some error caused server to close connection.\n"

#define SRV_PORT 8080

/*
** srv_process.c
*/

int					srv_process_line(t_srv *srv, char *str, char **response);

/*
** srv_init.c
*/

int					srv_init(t_rt *rt);

/*
** srv_shutdown.c
*/

int					srv_shutdown(t_rt *rt);

/*
** srv_loop.c
*/

void*				srv_loop(void* rt_pointer);

/*
** srv_request.c
*/

int					srv_request(t_rt *rt, char *str);

/*
** srv_ext.c
*/

int					srv_ext_client_process(t_rt *rt);
int					srv_ext_client_check(t_srv *srv);
int					srv_ext_client_disconnect(t_srv *srv);

/*
** srv_ext_data.c
*/

int					srv_ext_client_get_data(t_srv *srv);
int					srv_ext_client_update_str(t_srv *srv);
int					srv_ext_client_parse(t_srv *srv);
int					srv_ext_client_str_parse(t_srv *srv, unsigned long *line_begin);
int					srv_ext_client_parse_helper(t_srv *srv, unsigned long line_begin);

/*
** srv_parse.c
*/

t_msg				srv_parse_str(t_srv *srv, const char* request);

/*
** srv_utils.c
*/

int					msleep(long msec);
void				*null(int a);

#endif
