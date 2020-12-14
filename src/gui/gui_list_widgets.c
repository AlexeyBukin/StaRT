/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_list_widgets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:05:02 by rtacos            #+#    #+#             */
/*   Updated: 2020/12/08 17:22:10 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				push_widgets(GtkTreeStore *store, t_obj *obj,
										GtkTreeIter *parent)
{
	GtkTreeIter		iter;
	size_t			i;

	gtk_tree_store_append(store, &iter, parent);
	gtk_tree_store_set(store, &iter, COLUMN_TITLE, obj->name, -1);
	if (obj->type != OBJ_GROUP)
		return (0);
	i = -1;
	while (++i < obj->content.group.child_num)
		if (obj->content.group.children[i]->type == OBJ_GROUP)
			push_widgets(store, obj->content.group.children[i], &iter);
	i = -1;
	while (++i < obj->content.group.child_num)
		if (obj->content.group.children[i]->type == OBJ_CONTAINER)
			push_widgets(store, obj->content.group.children[i], &iter);
	return (0);
}

void			gui_add_widgets_to_tree(GtkTreeStore *store, t_rt *user_data,
															int type_box)
{
	t_obj *obj;

	obj = user_data->scene->main_group;
	if (type_box == OBJECT)
		push_widgets(store, obj, NULL);
}
