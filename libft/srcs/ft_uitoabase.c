/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:08:58 by tjose             #+#    #+#             */
/*   Updated: 2017/02/02 15:20:02 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen_base(uintmax_t a, int base)
{
	int counter;

	if (a == 0)
		return (1);
	counter = 0;
	while (a)
	{
		a /= base;
		counter++;
	}
	return (counter);
}

static char	*convert_base(char *result, uintmax_t holder, int base, int length)
{
	if (!holder)
		result[length] = '0';
	while (holder)
	{
		if (holder % base > 9)
			result[length] = holder % base + 'A' - 10;
		else
			result[length] = holder % base + '0';
		length--;
		holder /= base;
	}
	return (result);
}

char		*ft_uitoabase(uintmax_t value, int base)
{
	char	*result;
	int		length;

	if (base < 2)
		return (NULL);
	length = numlen_base(value, base);
	if (!(result = malloc(sizeof(char) * length + 1)))
		return (NULL);
	result[length] = '\0';
	return (convert_base(result, value, base, length - 1));
}
