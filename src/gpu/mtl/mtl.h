/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:59:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/25 16:46:37 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTL_H
# define MTL_H

typedef void			t_mtl;
typedef void			t_texture_rgba;

t_mtl					*mtl_init();

int						mtl_lib_load_source(t_mtl *mtl, char *libstr);

int						mtl_texture_add(t_mtl *mtl, int width, int height);
t_texture_rgba			*mtl_texture_get_ptr(t_mtl *mtl, int index);
int						mtl_texture_get_width(t_mtl *mtl, int index);
int						mtl_texture_get_height(t_mtl *mtl, int index);
int						mtl_texture_get_stride(t_mtl *mtl, int index);

#endif
