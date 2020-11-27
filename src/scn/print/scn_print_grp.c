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

void		scn_print_obj_common_params(t_tfm *trf)
{
	ft_printf("pos <%f, %f, %f> ",
		   trf->pos_local.x, trf->pos_local.y, trf->pos_local.z);
	ft_printf("angle [<%f, %f, %f>, <%f, %f, %f>, <%f, %f, %f>]\n",
			  trf->rot_local.x.x, trf->rot_local.x.y, trf->rot_local.x.z,
			  trf->rot_local.y.x, trf->rot_local.y.y, trf->rot_local.y.z,
			  trf->rot_local.z.x, trf->rot_local.z.y, trf->rot_local.z.z);
}

void		scn_print_obj_params(t_obj *obj, int tab_num)
{
	write_tabs(tab_num);
	ft_printf("%s id %d %s ", obj->name, obj->id,
			  obj->visible == TRUE ? "VISIBLE" : "NOT VISIBLE");
	if (obj->type == OBJ_CONTAINER)
	{
		if (obj->content.container.shape_type == SHP_SPHERE)
			ft_printf("shape SPHERE rad %f ", obj->content.container.shape.sphere.radius);
		else if (obj->content.container.shape_type == SHP_PLANE)
			ft_printf("shape PLANE ");
		else if (obj->content.container.shape_type == SHP_CONE)
			ft_printf("shape CONE rad %f len %f ", obj->content.container.shape.cone.radius,
					obj->content.container.shape.cone.length);
		else if (obj->content.container.shape_type == SHP_CYLINDER)
			ft_printf("shape CYLINDER rad %f len %f ", obj->content.container.shape.cylinder.radius,
					obj->content.container.shape.cylinder.length);
		else
		{
			ft_printf("shape UNKNOWN ");
			return (scn_print_obj_common_params(&obj->transform));
		}
		ft_printf(" material_name %s ", obj->content.container.material->name);
	}
	scn_print_obj_common_params(&obj->transform);
}

int		scn_print_grp_rec(t_obj *obj, int tab_num)
{
	t_obj_group		grp;
	size_t			i;

	if (obj == NULL)
		return (rt_err("scn_print_grp(): obj was given as a NULL pointer"));
	scn_print_obj_params(obj, tab_num);
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
