/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:44:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/23 23:45:34 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GUI_H
# define GUI_H

# include "rt_types.h"

int				gui_loop(t_rt *rt, int ac, char **av);
int				gui_init(t_rt *rt);
int				gui_deinit(t_rt *rt);

#endif
