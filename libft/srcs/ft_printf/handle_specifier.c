/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:43:16 by tjose             #+#    #+#             */
/*   Updated: 2017/02/22 14:33:14 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_specifier(char c, t_mods *mods)
{
	if (c == 'D' || c == 'C' || c == 'O' ||
		c == 'U' || c == 'S')
	{
		mods->length = l;
		c += 32;
	}
	if (c == 'p')
	{
		mods->length = l;
		mods->flags.hash = yes;
	}
	mods->specifier = c;
	return (1);
}
