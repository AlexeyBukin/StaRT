//
// Created by Hugor Chau on 12/14/20.
//

#ifndef START_CMD_RENDER_H
#define START_CMD_RENDER_H
# include "srv_types.h"
# include "rt_types.h"
# include "cmd_types.h"

/*
**		cmd_on_render
*/

int		cmd_on_render(t_rt *rt, char *filename,
						t_size2 tile, int tile_num);

/*
**		cmd_render_read
*/

int		cmd_render_read_name(t_parser *parser, char **filename);
int		cmd_render_read_width(t_parser *parser, size_t *w);
int		cmd_render_read_height(t_parser *parser, size_t *h);
int		cmd_render_read_tile_num(t_parser *parser, int *tile_num);
int		cmd_render_read_square(t_parser *parser, t_size2 *square);

#endif
