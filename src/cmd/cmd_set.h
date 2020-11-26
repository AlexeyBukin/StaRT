
#ifndef CMD_SET_H
# define CMD_SET_H

# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"

/*
**				cmd/set
*/

t_msg				cmd_set(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_sphere
*/

t_msg				cmd_set_sphere(t_rt *rt, t_parser *parser, t_obj *dest);
int 				cmd_set_sphere_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_plane
*/

t_msg				cmd_set_plane(t_rt *rt, t_parser *parser, t_obj *dest);
int 				cmd_set_plane_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_material
*/

int 				cmd_set_material_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cylinder
*/

t_msg				cmd_set_cylinder(t_rt *rt, t_parser *parser, t_obj *dest);
int					cmd_set_cylinder_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_cone
*/

t_msg				cmd_set_cone(t_rt *rt, t_parser *parser, t_obj *dest);
int					cmd_set_cone_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_group
*/

t_msg				cmd_set_group(t_rt *rt, t_parser *parser, t_obj *dest);
int					cmd_set_group_default(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_material
*/

t_msg				cmd_set_material(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_camera
*/

t_msg				cmd_set_camera(t_rt *rt, t_parser *parser);

/*
**				cmd/set/cmd_set_tools
*/

int					cmd_set_radius(t_parser *parser);

/*
**              cmd/set/cmd_set_transform_part
*/

int					cmd_read_transform_part(t_parser *parser);

/*
**              cmd/set/cmd_set_object_attributes
*/

int				cmd_set_visibility(t_parser *parser);
int				cmd_set_name(t_rt *rt, t_parser *parser);
int				cmd_set_grp(t_rt *rt, t_parser *parser);
int				cmd_set_mat(t_rt *rt, t_parser *parser);

#endif
