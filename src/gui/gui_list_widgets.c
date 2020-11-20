/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_list_widgets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/11/20 20:56:17 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

int			push_widgets(GtkWidget *in, t_obj *from)
{
	GtkWidget		*adds;
	GtkWidget		*list;
	GtkWidget		*row;
	size_t			i;
	if (from->type != OBJ_GROUP)
		return (0);
	i = 0;
	while (i < from->content.group.child_num)
	{
		if (from->content.group.children[i]->type == OBJ_CONTAINER)
		{
			row = gtk_list_box_row_new();
			gui_style(row);
			push_widgets(in, from->content.group.children[i]);
			gtk_container_add(GTK_CONTAINER(row), gtk_label_new(from->name));
			gtk_container_add(GTK_CONTAINER(in), row);
		}
		i++;
	}
	i = 0;
	while (i < from->content.group.child_num)
	{
		if (from->content.group.children[i]->type == OBJ_GROUP)
		{
			row = gtk_list_box_row_new();
			gui_style(row);
			adds = gtk_expander_new(from->name);
			list = gtk_list_box_new();
			gui_style(list);
			push_widgets(list, from->content.group.children[i]);
			gtk_container_add(GTK_CONTAINER(adds), list);
			gtk_container_add(GTK_CONTAINER(row), adds);
			gtk_container_add(GTK_CONTAINER(in), row);
			row = gtk_list_box_row_new();
			gui_style(row);
			gtk_container_add(GTK_CONTAINER(row), gtk_label_new(from->name));
			gtk_container_add(GTK_CONTAINER(in), row);
		}
		i++;
	}
	return (0);
		// gtk_list_box_set_selection_mode(GTK_LIST_BOX(in),
		// 									GTK_SELECTION_NONE);
		// row = gtk_list_box_row_new();
		// gui_style(row);
		// if (from->id == id_group)
		// {
		// 	push_widgets(in, from + 1, from->id);
		// 	gtk_container_add(GTK_CONTAINER(row), gtk_label_new(from->name));
		// 	gtk_container_add(GTK_CONTAINER(in), row);
		// }
		// else if (from->id != id_group && id_group != NONE)
		// {
		// 	adds = gtk_expander_new("grope");
		// 	list = gtk_list_box_new();
		// 	gui_style(list);
		// 	push_widgets(list, from, from->id);
		// 	gtk_container_add(GTK_CONTAINER(adds), list);
		// 	gtk_container_add(GTK_CONTAINER(row), adds);
		// 	gtk_container_add(GTK_CONTAINER(in), row);
		// 	gtk_list_box_unselect_row(GTK_LIST_BOX(in), GTK_LIST_BOX_ROW(row));
		// }
		
	// }
	
}

void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data, int type_box)
{
	// t_objs *objs_array = create_array_obj();
	// t_light *light_array = create_array_light();
	// GtkListBoxRow	*row;
	// GtkLabel		*lable;
	t_obj *obj;

	obj = user_data->scene->main_group;
	if (type_box == OBJECT)
		push_widgets(GTK_WIDGET(list_box), obj);
	// if (type_box == LIGHT)
	// lable = GTK_LABEL(gtk_label_new("objects"));
	// row = GTK_LIST_BOX_ROW(gtk_list_box_new());
	// gtk_container_add(GTK_CONTAINER(row), GTK_WIDGET(lable));
	// gtk_container_add(GTK_CONTAINER(list_box), GTK_WIDGET(row));
}
