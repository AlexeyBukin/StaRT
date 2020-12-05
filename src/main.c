/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:48:58 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/01 21:33:51 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO lock mutex on gui operations
//TODO unlock mutex after gui operations

t_obj			*add_test_obj(t_scn *scn, t_obj *grp, char *str, int type)
{
	t_obj		*obj_test_1;

	obj_init(&obj_test_1, ft_strdup(str), type);
	if (type == OBJ_CONTAINER)
		scn_add_to_group_obj(scn, grp, obj_test_1);
	if (type == OBJ_COPY)
		scn_add_to_group_copy(scn, grp, obj_test_1);
	if (type == OBJ_GROUP)
		scn_add_to_group_grp(scn, grp, obj_test_1);
	return (obj_test_1);
}
//
void			test(t_scn *scn)
{
	t_obj	*grp_test_1;
	t_obj	*grp_test_2;
	t_obj	*grp_test_2_a;
	t_obj	*grp_test_3;
	t_obj	*grp_test_4;
	/*
	**		scene objects
	*/
	add_test_obj(scn, scn->main_group, "test1", OBJ_CONTAINER);
	add_test_obj(scn, scn->main_group, "test2", OBJ_CONTAINER);
	add_test_obj(scn, scn->main_group, "test3", OBJ_CONTAINER);
	add_test_obj(scn, scn->main_group, "test4", OBJ_CONTAINER);
	grp_test_1 = add_test_obj(scn, scn->main_group, "grp_test_1", OBJ_GROUP);
	grp_test_2 = add_test_obj(scn, scn->main_group, "grp_test_2", OBJ_GROUP);
	grp_test_3 = add_test_obj(scn, scn->main_group, "grp_test_3", OBJ_GROUP);
	grp_test_4 = add_test_obj(scn, scn->main_group, "grp_test_4", OBJ_GROUP);

	/*
	**		grp_test_1
	*/
	add_test_obj(scn, grp_test_1, "test1_a", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_1, "test1_b", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_1, "test1_c", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_1, "test1_d", OBJ_CONTAINER);

	/*
	**		grp_test_2
	*/

	grp_test_2_a = add_test_obj(scn, grp_test_2, "test2_a", OBJ_GROUP);
	add_test_obj(scn, grp_test_2, "test2_b", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_2, "test2_c", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_2, "test2_d", OBJ_CONTAINER);

	/*
	**		grp_test_2_a
	*/
	add_test_obj(scn, grp_test_2_a, "test2_a_i", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_2_a, "test2_a_ii", OBJ_CONTAINER);
	add_test_obj(scn, grp_test_2_a, "test2_a_iii", OBJ_CONTAINER);
//	add_test_obj(scn, "grp_test_1_1", OBJ_GROUP);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);

//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);
//	scn_add_to_group_grp(scn, scn->main_group, grp_test_4);

}

int				main(int ac, char **av)
{
	t_rt				*rt;

	(void)ac;
	(void)av;
	if (rt_init(&rt))
		return (rt_error("Cannot init t_rt struct", 0));
	{

		test(rt->scene);
		if (srv_init(rt))
			return (rt_error("Cannot init server", 0));
		{
			if (gui_init(rt))
				return (rt_error("Cannot init GUI", 0));
			if (gui_loop(rt, ac, av))
				return (rt_error("Main loop quit in unexpected manner", 0));
			if (gui_deinit(rt))
				return (rt_error("Cannot deinit GUI", 0));
		}
 		if (srv_deinit(rt))
 			return (rt_error("Cannot deinit server", 0));
	}
	// scn_print(rt->scene);
//		if (srv_deinit(rt))
//			return (rt_error("Cannot deinit server", 0));
	// }
//	test(rt->scene);
//	scn_print(rt->scene);
	if (rt_deinit(rt))
		return (rt_error("Cannot deinit t_rt struct", 0));
	return (0);
}
