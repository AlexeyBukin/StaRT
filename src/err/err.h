/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:57:55 by kcharla           #+#    #+#             */
/*   Updated: 2020/09/07 15:57:55 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

int			rt_err(char *msg);
int			rt_error(char *msg, int ecode);

int			rt_warn(char *msg);
int			rt_warning(char *msg, int ecode);

#endif
