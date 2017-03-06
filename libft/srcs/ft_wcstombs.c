/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 16:23:29 by tjose             #+#    #+#             */
/*   Updated: 2017/01/20 16:45:28 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
	size_t src_i;
	size_t dest_i;

	src_i = 0;
	dest_i = 0;
	while (dest_i < n - 1)
		dest_i += (ft_wctomb(&s[dest_i], pwcs[src_i++]));
	s[dest_i] = '\0';
	return (dest_i);
}
