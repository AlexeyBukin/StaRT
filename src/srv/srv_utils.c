/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:09:40 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/02 16:10:42 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				msleep(long msec)
{
	struct timespec ts;
	int res;

	if (msec < 0)
	{
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;

	do {
		res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);

	return res;
}

void				*null(int a)
{
	(void)a;
	return (NULL);
}

static gboolean
srv_g_application_quit(gpointer void_app)
{
	g_application_quit(G_APPLICATION(void_app));
	return G_SOURCE_REMOVE;
}

void		srv_quit_gtk_app(t_rt *rt)
{
	GSource *source;

	if (rt == NULL)
		return ;
	source = g_idle_source_new();
	g_source_set_callback(source, srv_g_application_quit, rt->app, NULL);
	g_source_attach(source, rt->context);
}
