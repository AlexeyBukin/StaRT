/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:59:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 00:14:47 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTL_H
#define MTL_H

typedef void		t_mtl;

t_mtl		*mtl_init();

int			mtl_lib_load_source(t_mtl *mtl, char *libstr);

#endif
