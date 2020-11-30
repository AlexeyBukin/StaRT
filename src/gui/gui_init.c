/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:01 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 08:57:50 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

# define TOGGLE_SERVER_ON  "Click to start server"
# define TOGGLE_SERVER_OFF "Click to stop server"

static void button_server_clicked (GtkButton *source, t_rt *rt) {
	if (source == NULL || rt == NULL)
	{
		rt_err("Cannot start server");
		return ;
	}

//	gboolean  is_active = gtk_toggle_button_get_active(source);
	if (rt->server == NULL)
	{
		if (srv_init(rt))
			rt_err("Cannot start server");
		else
		{
			gtk_button_set_label(GTK_BUTTON(source), TOGGLE_SERVER_OFF);
		}
	}
	else
	{
		if (srv_deinit(rt))
			rt_err("Cannot stop server");
		else
		{
			gtk_button_set_label(GTK_BUTTON(source), TOGGLE_SERVER_ON);
		}
	}
}

static void activate (GtkApplication* app, t_rt *rt)
{
	GtkWidget *button_server;
	GtkWidget *window;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "StarRT Editor");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

	{
		button_server = gtk_button_new_with_label (TOGGLE_SERVER_ON);
		g_signal_connect (button_server, "clicked", G_CALLBACK (button_server_clicked), rt);
		gtk_container_add (GTK_CONTAINER (window), button_server);
	}

	gtk_widget_show_all (window);
}

int				gui_init(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	rt->app = gtk_application_new ("ru.school-21.start", G_APPLICATION_FLAGS_NONE);
	if (g_signal_connect (rt->app, "activate", G_CALLBACK (activate), rt) <= 0)
		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
	rt->context = g_main_context_default();
//	if (g_signal_connect (rt->app, "handle", G_CALLBACK (activate), rt) <= 0)
//		return (rt_err("Cannot connect \'activate\' signal to rt->app"));
//	g_application_add_main_option_entries()
	return (0);
}

int				gui_loop(t_rt *rt, int ac, char **av)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	return (g_application_run (G_APPLICATION (rt->app), ac, av));
}

int				gui_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	g_object_unref (rt->app);
	return (0);
}



//void make_toggle (void) {
//	GtkWidget *window, *toggle1, *toggle2;
//	GtkWidget *box;
//	const char *text;
//
//	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
//
//	text = "Hi, I’m a toggle button.";
//	toggle1 = gtk_toggle_button_new_with_label (text);
//
//	// Makes this toggle button invisible
//	gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (toggle1),
//								TRUE);
//
//	g_signal_connect (toggle1, "toggled",
//					  G_CALLBACK (output_state),
//					  NULL);
//	gtk_container_add (GTK_CONTAINER (box), toggle1);
//
//	text = "Hi, I’m a toggle button.";
//	toggle2 = gtk_toggle_button_new_with_label (text);
//	gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (toggle2),
//								FALSE);
//	g_signal_connect (toggle2, "toggled",
//					  G_CALLBACK (output_state),
//					  NULL);
//	gtk_container_add (GTK_CONTAINER (box), toggle2);
//
//	gtk_container_add (GTK_CONTAINER (window), box);
//	gtk_widget_show_all (window);
//}