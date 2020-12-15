/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:55:50 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/16 22:03:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			scn_print(t_scn *scn)
{
	if (!scn)
		return (rt_err("scn_print(): given pointer is NULL"));
	ft_printf("scene:\n");
	scn_print_txr(scn);
	scn_print_mat(scn);
	if (scn_print_grps(scn))
		return (-1);
	return (0);
}
