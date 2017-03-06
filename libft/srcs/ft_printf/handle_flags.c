/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:33:38 by tjose             #+#    #+#             */
/*   Updated: 2017/02/07 14:04:05 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_flags(const char *str, t_mods *mods)
{
	int i;

	i = 0;
	while (str[i] == '-' || str[i] == '+' || str[i] == ' '
		|| str[i] == '#' || str[i] == '0')
	{
		if (str[i] == '-')
			mods->flags.left_justify = 1;
		else if (str[i] == '+')
			mods->flags.show_sign = 1;
		else if (str[i] == ' ')
			mods->flags.show_space = 1;
		else if (str[i] == '#')
			mods->flags.hash = yes;
		else if (str[i] == '0')
			mods->flags.fill_zeroes = 1;
		i++;
	}
	return (i);
}
