
#include "rt.h"
#include "png.h"

t_msg		cmd_add_txr_error(t_parser *parser, char *message)
{
	txr_deinit(parser->texture);
	return (msg_warn(message));
}

int		add_txr(t_rt *rt, t_parser *parser)
{
//	FILE		*txr;
//	png_structp png;
//	png_infop info;
//	txr = fopen(parser->texture->filename, "wb");
//	if(!txr)
//		return (rt_err(""));
//	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//	if (!png)
//		return (-1);
//	info = png_create_info_struct(png);
//	png_bytep *row_pointers = NULL;
//	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
//	if (!row_pointers) return (-1);
//	int y;
//	for(y = 0; y < height; y++)
//	{
////		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
//		row_pointers[y] = (png_byte*)&(data[0]);
//	}
//	png_read_image(png, row_pointers);
//	png_read_end(png, NULL);
	if (scn_add_txr(rt->scene, parser->texture))
		return (rt_err(""));
	return (0);
}

t_msg		cmd_read_txr(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	while (*parser->cur != '\n' && *parser->cur != '\0')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax"));
		if (cmd_read_txr_type(parser))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax type"));
		if (cmd_read_txr_filename(parser))
			return (cmd_add_txr_error(parser, "cmd_read_txr(): bad syntax filename"));
	}
	if (add_txr(rt, parser))
		return (cmd_add_txr_error(parser, "cmd_read_txr(): can\'t add texture to scene"));
	return (msg_oks("cmd_add_txr(): success"));
}

int			init_txr_parser(t_rt *rt, t_parser *parser)
{
	(void)rt;
	(void)parser;
	txr_init(&parser->texture, parser->name, (t_size2){1, 1});
	return (0);
}

t_msg		cmd_add_txr(t_rt *rt, t_parser *parser)
{
	parser->cur += ft_strlen("texture");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_cone(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_cone(): bad name"));
	if (init_txr_parser(rt, parser))
		return (msg_err("cmd_add_cone(): critical malloc error"));
	return (cmd_read_txr(rt, parser));
}
