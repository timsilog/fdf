/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nospec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:53:43 by tjose             #+#    #+#             */
/*   Updated: 2017/02/06 13:30:48 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** If there's no specifier and no characters to print, nothing is printed.
** If there are characters to print, the first printable character is
** printed with the specified width. '0' and '-' flags work.
*/

static void	adjust_nsmods(t_mods *mods)
{
	mods->flags.show_sign = 0;
	mods->flags.show_space = 0;
	mods->flags.hash = 0;
	mods->length = 0;
	mods->precision = -1;
}

int			handle_nospec(t_mods *mods)
{
	char	*ans;
	char	temp[2];
	int		size;

	adjust_nsmods(mods);
	temp[0] = mods->specifier;
	temp[1] = '\0';
	size = get_size(temp, mods);
	if (!(ans = malloc(sizeof(char) * size + 1)))
		return (-1);
	mods->flags.left_justify ? place_left(mods, &ans, size, temp) :
		place_right(mods, &ans, size, temp);
	ft_putstr(ans);
	free(ans);
	return (size);
}
