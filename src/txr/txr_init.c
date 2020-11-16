/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "txr.h"

//scn_check_name checks if name is unique and strlen() > 0
//if not returns error

int		txr_init(t_txr **dest, t_scn *scn, char *name, t_size2 size)
{
	t_txr 	*txr;

	if (size.x == 0 || size.y == 0)
		return (rt_err("Invalid texture size"));
	if (txr_init_default(&txr, scn, name))
		return (rt_err("Cannot init texture base"));
	txr->type = TXR_RGB_8;
	txr->gpu_type = TXR_GPU_UNSYNCED;
	txr->width = size.x;
	txr->height = size.y;
	txr->stride = size.x * 3;
	txr->content = ft_memalloc(sizeof(char) * txr->stride * txr->height);
	if (txr->content == NULL)
	{
		txr_deinit(&txr);
		return (rt_err("Cannot init texture"));
	}
	*dest = txr;
	return (0);
}

int		txr_init_default(t_txr **dest, t_scn *scn, char *name)
{
	t_txr		*txr;

	if (dest == NULL || name == NULL || scn == NULL)
		return (rt_err("Given pointer is NULL"));
	if (scn_name_check(scn, name))
		return (rt_err("Incorrect name"));
	txr = ft_memalloc(sizeof(t_txr));
	if (txr == NULL)
		return (rt_err("Malloc returned NULL"));
	txr->id = scn_id();
	txr->name = name;
	txr->filename = NULL;
	txr->type = TXR_NONE;
	txr->gpu_type = TXR_GPU_NONE;
	txr->width = 0;
	txr->height = 0;
	txr->stride = 0;
	txr->content = NULL;
	return (0);
}

int		txr_deinit(t_txr **txr)
{
	if (txr == NULL)
		return (rt_err("Given pointer is NULL"));
	if (*txr == NULL)
		return (rt_err("Dereference to NULL"));
	ft_free((*txr)->name);
	ft_free((*txr)->content);
	ft_free(*txr);
	*txr = NULL;
	return (0);
}

//txr_init_gpu_synced?
//txr_init_gpu_const?
//int		txr_init_gpu_synced(t_txr **dest, t_rt *rt, char *name, t_size2 size)
//{
//	t_txr 	*txr;
//
//	if (size.x == 0 || size.y == 0)
//		return (rt_err("Invalid texture size"));
//	if (txr_init_default(&txr, scn, name))
//		return (rt_err("Cannot init texture base"));
//	txr->type = TXR_RGB_8;
//	txr->gpu_type = TXR_GPU_UNSYNCED;
//	txr->width = size.x;
//	txr->height = size.y;
//	txr->stride = size.x * 3;
//	txr->content = ft_memalloc(sizeof(char) * txr->stride * txr->height);
//	if (txr->content == NULL)
//	{
//		txr_deinit(&txr);
//		return (rt_err("Cannot init texture"));
//	}
//	*dest = txr;
//	return (0);
//}
