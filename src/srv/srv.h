/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 10:19:54 by kcharla          ###   ########.fr       */
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
# define SRV_BUSY  "Server is busy. Try later.\n"
# define SRV_ERR   "Some error caused server to close connection.\n"
# define SRV_EXIT  "Closing connection. Have a nice day :)"
# define SRV_SHUT  "Shutting down..."

# define SRV_PORT 8080

# define SRV_STR_ERR_MLK "Server malloc() error."
# define SRV_STR_ERR_PARSE "Server parsing line error."
# define SRV_STR_ERR_READ "Server read() error."
# define SRV_STR_SHUT "Connection is closed, shutting down..."
# define SRV_STR_CLOSE "Connection is closed, server is running..."

/*
** srv_process.c
*/

int					srv_process_line(t_srv *srv, char *str, char **response);

/*
** srv_init.c
*/

int					srv_init(t_rt *rt);

/*
** srv_deinit.c
*/

int					srv_deinit(t_rt *rt);

/*
** srv_loop.c
*/

void				*srv_loop(void *rt_pointer);

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
int					srv_ext_client_str_parse(t_srv *srv,
								unsigned long *line_begin);
int					srv_ext_client_parse_helper(t_srv *srv,
								unsigned long line_begin);

/*
** srv_parse.c
*/

t_msg				srv_parse_str(t_srv *srv, const char *request);

/*
** srv_utils.c
*/

void				srv_quit_gtk_app(t_rt *rt);
int					msleep(long msec);
void				*null(int a);

#endif
