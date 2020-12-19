/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_vfx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <hchau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by hchau             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CMD_VFX_H
# define RT_CMD_VFX_H

t_msg		cmd_vfx_sum(t_rt *rt, t_parser *parser);
t_msg		cmd_vfx(t_rt *rt, t_parser *parser);
int			cmd_vfx_read_name(t_rt *rt, t_parser *parser, t_list **txr);
int			cmd_vfx_sum_dest(t_rt *rt, t_parser *parser);
t_msg		cmd_vfx_sum_read(t_rt *rt, t_parser *parser);
int			vfx_add_txr_to_scn(t_rt *rt, t_parser *parser);

#endif
