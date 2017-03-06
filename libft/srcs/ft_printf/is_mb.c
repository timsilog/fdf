/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 22:13:48 by tjose             #+#    #+#             */
/*   Updated: 2017/01/30 16:58:23 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks if current character of a given string is a complete
** multibyte character.
** If there's only part of a mb char then it returns false.
** Otherwise returns number of characters read.
** (Works with single-byte characters as well)
** 1b - 0xxx xxxx (0 < s[i])
** 2b - 110x xxxx  10xx xxxx (s[i] < -32)
** 3b - 1110 xxxx  10xx xxxx  10xx xxxx (s[i] < -16)
** 4b - 1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx (s[i] < -8)
*/

static int	is_n_bytes(char *s, int n)
{
	int i;

	i = 1;
	while (s[i] && i < n)
	{
		if (s[i] >= -64)
			return (0);
		i++;
	}
	if (i == n)
		return (n);
	return (0);
}

int			is_mb(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] > 0)
		return (1);
	else if (s[i] > -64 && s[i] < -32)
		return (is_n_bytes(s, 2));
	else if (s[i] >= -32 && s[i] < -16)
		return (is_n_bytes(s, 3));
	else if (s[i] >= -16 && s[i] < -8)
		return (is_n_bytes(s, 4));
	else
		return (0);
}
