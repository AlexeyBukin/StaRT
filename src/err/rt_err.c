/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:40:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/09/07 12:41:44 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

int			rt_err(char *msg)
{
	ft_printf("Error: %s", msg);
	return (-1);
}

int			rt_error(char *msg, int ecode)
{
	ft_printf("Error: (%i) %s", ecode, msg);
	return (ecode);
}
