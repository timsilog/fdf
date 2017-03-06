/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:38:35 by tjose             #+#    #+#             */
/*   Updated: 2017/02/07 13:52:30 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				handle_number(va_list tags, t_mods *mods)
{
	char		*ans;
	char		*str_n;
	int			size;
	char		c;
	int			ret;

	c = mods->specifier;
	if (c == 'u' || c == 'x' || c == 'o' || c == 'X' || c == 'p')
		str_n = convert_ulength(tags, mods, c);
	else
		str_n = convert_length(tags, mods, c);
	size = get_size(str_n, mods);
	if (!(ans = malloc(sizeof(char) * size + 1)))
		return (-1);
	mods->flags.left_justify ? place_left(mods, &ans, size, str_n) :
		place_right(mods, &ans, size, str_n);
	ft_putstr(ans);
	ret = ft_strlen(ans);
	free(str_n);
	free(ans);
	return (ret);
}
