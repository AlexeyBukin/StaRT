//
// Created by Hugor Chau on 11/19/20.
//

# include "rt.h"

void			print_vec3(t_vec3 vec)
{
	ft_printf("<%.3f, %.3f, %.3f> ",
			  vec.x, vec.y, vec.z);
}

void			print_vec2(t_vec2 vec)
{
	ft_printf("<%.3f, %.3f> ",
			  vec.x, vec.y);
}

void			scn_print_mat(t_scn *scn)
{
	size_t		i;

	i = 0;
	ft_printf("materials:\n");
	while (i < scn->materials_num)
	{
		ft_printf("\t%s id %d ",
				scn->materials[i]->name, scn->materials[i]->id);
		ft_printf("-m ");
		ft_printf("%.3f ", scn->materials[i]->content.pbr.metalness);
		ft_printf("-r ");
		ft_printf("%.3f ", scn->materials[i]->content.pbr.roughness);
		ft_printf("-i ");
		ft_printf("%.3f ", scn->materials[i]->content.pbr.ior);
		ft_printf("-t ");
		ft_printf("%.3f ", scn->materials[i]->content.pbr.transparency);
		ft_printf("-a ");
		print_vec3(scn->materials[i]->content.pbr.albedo);
		ft_printf("-f ");
		print_vec3(scn->materials[i]->content.pbr.f0);
		ft_printf("\n");
		i++;
	}
}
