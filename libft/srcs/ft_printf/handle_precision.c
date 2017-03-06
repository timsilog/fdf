/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:59:19 by tjose             #+#    #+#             */
/*   Updated: 2017/02/07 14:31:25 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_precision(const char *str, t_mods *mods, va_list tags)
{
	int			i;

	i = 0;
	mods->precision = 0;
	if (str[++i] == '*')
	{
		mods->precision = va_arg(tags, int);
		return (2);
	}
	while (ft_isdigit(str[i]))
		mods->precision = mods->precision * 10 + (str[i++] - '0');
	return (i);
}
