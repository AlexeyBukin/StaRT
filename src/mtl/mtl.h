/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:59:42 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/10 00:23:32 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTL_H
# define MTL_H

typedef void			t_mtl;
typedef void			t_texture_rgba;

t_mtl					*mtl_init();

/*
** return 0 on success
*/

int						mtl_lib_load_source(t_mtl *mtl, char *libstr);

/*
** return non-negative texture index on success
*/

int						mtl_texture_create_target(t_mtl *mtl, int width, int height);

/*
** return non-null pointer on success
*/

t_texture_rgba			*mtl_texture_get_ptr_target(t_mtl *mtl, int index);

/*
** return positive (>0) int on success
*/

int						mtl_texture_get_width(t_mtl *mtl, int index);
int						mtl_texture_get_height(t_mtl *mtl, int index);
int						mtl_texture_get_stride(t_mtl *mtl, int index);

int						mtl_texture_resource_rgba8_load(t_mtl *mtl, void *image_data, int width, int height);
int						mtl_texture_target_rgba8_load(t_mtl *mtl, void *image_data, int width, int height);
int						mtl_texture_target_save(t_mtl *mtl, int index, char *filepath);

/*
** return 0 on success
*/

int						mtl_buffer_load_info(t_mtl *mtl, void *ptr, int len);
int						mtl_buffer_load_objects(t_mtl *mtl, void *ptr, int len);
int						mtl_buffer_load_materials(t_mtl *mtl, void *ptr, int len);
int						mtl_buffer_load_lights(t_mtl *mtl, void *ptr, int len);

int						mtl_kernel_run(t_mtl *mtl, char *kernel_name, int target_index);

#endif
