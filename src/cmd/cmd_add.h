#ifndef CMD_ADD_H
#define CMD_ADD_H

# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"
/*
**				cmd/add
*/

t_msg           	cmd_add_sphere(t_rt *rt, t_parser *parser);
t_msg				cmd_add_plane(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cone(t_rt *rt, t_parser *parser);
t_msg				cmd_add_cylinder(t_rt *rt, t_parser *parser);
t_msg           	cmd_add_group(t_rt *rt, t_parser *parser);
t_msg				cmd_add_camera(t_rt *rt, t_parser *parser);
t_msg				cmd_add_material(t_rt *rt, t_parser *parser);

/*
**				cmd_add
*/

t_msg				cmd_add_error(t_parser *parser, char *error_message);
t_msg               cmd_add(t_rt *rt, t_parser *parser);

#endif
