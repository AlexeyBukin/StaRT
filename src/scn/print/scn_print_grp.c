//
// Created by Hugor Chau on 11/19/20.
//

# include "rt.h"

void	write_tabs(int tab_num)
{
	while (tab_num)
	{
		ft_printf("\t");
		tab_num--;
	}
}

void		scn_print_obj_params(int id, char *name, t_tfm *trf, int tab_num)
{
	write_tabs(tab_num);
	ft_printf("%s id %d pos <%f, %f, %f>\n", name, id,
		   trf->pos_local.x, trf->pos_local.y, trf->pos_local.z);
//	printf("%*s%s id %d pos <%d, %d, %d>\n", tab_num * 4, 1, name, id,
//		   (int)trf->pos_local.x, (int)trf->pos_local.y, (int)trf->pos_local.z);
}

int		scn_print_grp_rec(t_obj *obj, int tab_num)
{
	t_obj_group		grp;
	size_t			i;

	if (obj == NULL)
		return (rt_err("scn_print_grp(): obj was given as a NULL pointer"));
	scn_print_obj_params(obj->id, obj->name, &obj->transform, tab_num);
	if (obj->type != OBJ_GROUP)
		return (0);
	grp = obj->content.group;
	write_tabs(tab_num);
	ft_printf("group %s:\n", obj->name);
	i = 0;
	while (i < grp.child_num)
	{
		if (grp.children[i]->type == OBJ_COPY)
		{
			if (scn_print_grp_rec(grp.children[i], tab_num + 1))
				return (rt_err("scn_print_grp_rec(): couldn\'t get info about obj"));
		}
		i++;
	}
	i = 0;
	while (i < grp.child_num)
	{
		if (grp.children[i]->type == OBJ_CONTAINER)
		{
			if (scn_print_grp_rec(grp.children[i], tab_num + 1))
				return (rt_err("scn_print_grp_rec(): couldn\'t get info about obj"));
		}
		i++;
	}
	i = 0;
	while (i < grp.child_num)
	{
		if (grp.children[i]->type == OBJ_GROUP)
		{
			if (scn_print_grp_rec(grp.children[i], tab_num + 1))
				return (rt_err("scn_print_grp_rec(): couldn\'t get info about obj"));
		}
		i++;
	}
	return (0);
}

int		scn_print_grps(t_scn *scn)
{
	return (scn_print_grp_rec(scn->main_group, 0));
}
