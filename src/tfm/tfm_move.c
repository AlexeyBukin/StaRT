/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfm_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//int		tfm_update(t_tfm *tfm)
//{
//	if (tfm == NULL)
//		return (rt_err("Given pointer is NULL"));
//	if (tfm->parent == NULL)
//		return (0);
//	if (tfm_update(tfm->parent))
//		return (rt_err("Cannot update transform parent"));
//	tfm->pos_global =  vec3_plus(tfm->parent->pos_global, tfm->pos_local);
//	tfm->pos_global = vec3_plus();
//
//}
//
//int		tfm_update_rec(t_tfm *tfm)
//{
//	if (tfm == NULL)
//		return (rt_err("Given pointer is NULL"));
//	if (tfm->parent == NULL)
//		return (0);
//	if (tfm_update(tfm->parent))
//		return (rt_err("Cannot update transform parent"));
//	tfm->pos_global =  vec3_plus(tfm->parent->pos_global, tfm->pos_local);
//	tfm->pos_global = vec3_plus();
//
//}
