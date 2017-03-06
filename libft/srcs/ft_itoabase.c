/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:08:58 by tjose             #+#    #+#             */
/*   Updated: 2017/01/12 13:58:11 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen_base(intmax_t a, int base)
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

static char	*convert_base(char *result, intmax_t holder, int base, int length)
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

static char	*prep_result(intmax_t value, int length, int base)
{
	char *result;

	if (value < 0 && base == 10)
	{
		if (!(result = malloc(sizeof(char) * length + 2)))
			return (NULL);
		result[0] = '-';
		result[length + 1] = '\0';
	}
	else
	{
		if (!(result = malloc(sizeof(char) * length + 1)))
			return (NULL);
		result[length] = '\0';
	}
	return (result);
}

char		*ft_itoabase(intmax_t value, int base)
{
	char	*result;
	int		length;

	if (base < 2)
		return (NULL);
	length = (value < 0 && base == 10) ? 1 : 0;
	length += numlen_base(value, base);
	if (!(result = prep_result(value, length, base)))
		return (NULL);
	value = (value < 0) ? -value : value;
	return (convert_base(result, value, base, length - 1));
}
