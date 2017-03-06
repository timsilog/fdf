/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:59:31 by tjose             #+#    #+#             */
/*   Updated: 2017/02/07 14:13:45 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_width(const char *str, t_mods *mods, va_list tags)
{
	int	i;

	i = 0;
	if (str[i] == '*')
	{
		mods->width = va_arg(tags, int);
		if (mods->width < 0)
		{
			mods->flags.left_justify = 1;
			mods->width *= -1;
		}
		return (1);
	}
	if (ft_isdigit(str[i]))
		mods->width = 0;
	while (ft_isdigit(str[i]))
		mods->width = mods->width * 10 + (str[i++] - '0');
	return (i);
}
