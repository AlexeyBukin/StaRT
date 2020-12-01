#include "rt.h"

int				lgt_init(t_obj **dest, char *name)
{
	t_obj		*cont;

	if (name == NULL || dest == NULL)
		return (rt_err("Given pointer is NULL"));
	cont = ft_memalloc(sizeof(t_obj));
	if (cont == NULL)
		return (rt_err("Cannot malloc container object"));

	cont->id = scn_id();
	cont->name = name;
	cont->parent = NULL;
	cont->visible = TRUE;

	cont->type = OBJ_LIGHT;
	cont->content.light.lgt_type = LGT_POINT;
	cont->content.light.light.intensity = 1;
	cont->content.light.light.color = vec3(1, 1, 1);

	tfm_init(&(cont->transform));
	cont->transform.parent = NULL;

	*dest = cont;
	return (0);
}

int				lgt_deinit(t_obj *cont)
{
	if (cont == NULL)
		return (rt_err("Given pointer is NULL"));
	if (cont->type != OBJ_LIGHT)
		return (rt_err("Cannot deinit object: not a container"));
	ft_free(cont->name);
	ft_free(cont);
	return (0);
}
