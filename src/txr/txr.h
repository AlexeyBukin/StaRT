/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TXR_H
# define TXR_H

# include "scn_types.h"
# include "txr_types.h"

int		txr_init(t_txr **dest, char *name, t_size2 size);
int		txr_init_default(t_txr **dest, char *name);
int		txr_deinit(t_txr *txr);

int		txr_rgba_to_rgb(t_txr *rgba, t_txr **rgb_dest);

#endif
