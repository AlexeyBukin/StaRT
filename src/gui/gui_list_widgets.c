/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_list_widgets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/11/20 18:16:28 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

enum e_id_obj
{
	NONE,
	ONE_ELEM,
	GROUP_1,
	GROUP_2,
	GROUP_IN_2
};

enum e_type_obj
{
	ELEM,
	GROUP
};

typedef struct	s_objs
{
	char *label;
	int type;
	int id;
}				t_objs;

typedef struct	s_light
{
	char *label;
}				t_light;

typedef struct s_gui_list_group
{
	int		id;
	void	*next;
}				t_gui_list_group;


static t_objs			set_label_and_type(char *label, int id)
{
	t_objs elem;
	
	elem.label = ft_strdup(label);
	elem.id = id;
	if (id == ONE_ELEM)
		elem.type = ELEM;
	else
		elem.type = GROUP;
	return (elem);
}

static t_objs			*create_array_obj()
{
	t_objs *arr = malloc(sizeof(t_objs) * 11);
	arr[0] = set_label_and_type("1", ONE_ELEM);
	arr[1] = set_label_and_type("2.1", GROUP_1);
	arr[2] = set_label_and_type("2.2", GROUP_1);
	arr[3] = set_label_and_type("2.3", GROUP_1);
	arr[4] = set_label_and_type("3.1", GROUP_2);
	arr[5] = set_label_and_type("3.2", GROUP_2);
	arr[6] = set_label_and_type("3.3.1", GROUP_IN_2);
	arr[7] = set_label_and_type("3.3.2", GROUP_IN_2);
	arr[8] = set_label_and_type("4", ONE_ELEM);
	arr[9] = set_label_and_type("5", ONE_ELEM);
	arr[10] = set_label_and_type("\0", NONE);
	return (arr);
}

// static t_light			*create_array_light()
// {
// 	t_light *arr = malloc(3 * sizeof(t_light));
// 	return (arr);
// }

void			push_widgets(GtkWidget *in, t_objs *from, int id_group)
{
	// GtkWidget		*label;
	GtkWidget		*adds;
	GtkWidget		*list;
	GtkWidget		*row;
// (void)in;
// (void)from;
	if (from->label[0] == '\0')
		return ;
	else
	{
		// gtk_list_box_set_selection_mode(GTK_LIST_BOX(in),
		// 									GTK_SELECTION_NONE);
		row = gtk_list_box_row_new();
		gui_style(row);
		if (from->id == id_group)
		{
			push_widgets(in, from + 1, from->id);
			gtk_container_add(GTK_CONTAINER(row), gtk_label_new(from->label));
			gtk_container_add(GTK_CONTAINER(in), row);
		}
		else if (from->id != id_group && id_group != NONE)
		{
			adds = gtk_expander_new("grope");
			list = gtk_list_box_new();
			gui_style(list);
			push_widgets(list, from, from->id);
			gtk_container_add(GTK_CONTAINER(adds), list);
			gtk_container_add(GTK_CONTAINER(row), adds);
			gtk_container_add(GTK_CONTAINER(in), row);
			gtk_list_box_unselect_row(GTK_LIST_BOX(in), GTK_LIST_BOX_ROW(row));
		}
		
	}
	
}

void			gui_add_widgets_to_list(GtkListBox *list_box, t_rt *user_data, int type_box)
{
	(void)user_data;
	(void)list_box;
	t_objs *objs_array = create_array_obj();
	t_gui_list_group	*g_list;
	// t_light *light_array = create_array_light();
	// GtkListBoxRow	*row;
	// GtkLabel		*lable;

	if (type_box == OBJECT)
	{
		g_list = malloc(sizeof(t_gui_list_group));
		g_list->next = NULL;
		push_widgets(GTK_WIDGET(list_box), objs_array, ONE_ELEM);
	}
	// if (type_box == LIGHT)
	// lable = GTK_LABEL(gtk_label_new("objects"));
	// row = GTK_LIST_BOX_ROW(gtk_list_box_new());
	// gtk_container_add(GTK_CONTAINER(row), GTK_WIDGET(lable));
	// gtk_container_add(GTK_CONTAINER(list_box), GTK_WIDGET(row));
}