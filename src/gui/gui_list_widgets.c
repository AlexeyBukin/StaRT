/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_list_widgets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/11/25 21:25:25 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

// static void	gui_expander_callback(GObject *object, GParamSpec *param_spec,
// 													gpointer user_data)
// {
// 	(void)param_spec;
// 	(void)user_data;
// 	GtkExpander *expander;

// 	expander = GTK_EXPANDER(object);

// 	if (gtk_expander_get_expanded(expander))
// 		gtk_widget_set_name(GTK_WIDGET(expander), "expander-open");
// 	else
// 		gtk_widget_set_name(GTK_WIDGET(expander), "expander-closer");
// 	gui_style(GTK_WIDGET(expander));
// }

int			push_widgets(GtkWidget *in, t_obj *from, int shift)
{
	GtkWidget		*expander;
	GtkWidget		*list;
	GtkWidget		*row;
	size_t			i;
	GtkWidget		*label;

	row = gtk_list_box_row_new();
	gui_style(row);
	if (from->type == OBJ_GROUP)
	{
		expander = gtk_expander_new(from->name);
		gtk_widget_set_margin_start(GTK_WIDGET(expander), shift);
		shift += 10;
		gtk_expander_set_label_fill(GTK_EXPANDER(expander), TRUE);
		list = gtk_list_box_new();
		gui_style(list);
		gtk_container_add(GTK_CONTAINER(expander), list);
		gtk_container_add(GTK_CONTAINER(row), expander);
		gtk_widget_set_name(GTK_WIDGET(row), "row_expander");
		gui_style(row);
		gtk_container_add(GTK_CONTAINER(in), row);
	}
	else
	{
		label = gtk_label_new(from->name);
		gtk_label_set_xalign(GTK_LABEL(label), 0.06);
		gtk_container_add(GTK_CONTAINER(row), label);
		gtk_container_add(GTK_CONTAINER(in), row);
		return (0);
	}
	i = 0;
	while (i < from->content.group.child_num)
	{
		if (from->content.group.children[i]->type == OBJ_GROUP)
			push_widgets(list, from->content.group.children[i], shift);
		i++;
	}
	i = 0;
	while (i < from->content.group.child_num)
	{
		if (from->content.group.children[i]->type == OBJ_CONTAINER)
			push_widgets(list, from->content.group.children[i], shift);
		i++;
	}
	return (0);
}

void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data, int type_box)
{
	t_obj *obj;

	obj = user_data->scene->main_group;
	if (type_box == OBJECT)
		push_widgets(GTK_WIDGET(list_box), obj, 0);
	// if (type_box == LIGHT)
	// lable = GTK_LABEL(gtk_label_new("objects"));
	// row = GTK_LIST_BOX_ROW(gtk_list_box_new());
	// gtk_container_add(GTK_CONTAINER(row), GTK_WIDGET(lable));
	// gtk_container_add(GTK_CONTAINER(list_box), GTK_WIDGET(row));
}
