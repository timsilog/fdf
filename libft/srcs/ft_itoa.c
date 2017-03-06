/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:23:11 by tjose             #+#    #+#             */
/*   Updated: 2017/02/02 17:44:46 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_num(char *s, intmax_t n, int flag)
{
	int		i;
	int		len;

	i = 0;
	len = ft_numlen(n) + flag;
	s[len--] = '\0';
	while (len >= 0)
	{
		s[len--] = n % 10 + '0';
		n /= 10;
	}
	if (flag)
		s[0] = '-';
	return (s);
}

char		*ft_itoa(intmax_t n)
{
	int			neg_flag;
	int			i;
	char		*s;

	i = 0;
	neg_flag = 0;
	if (n < 0)
	{
		neg_flag++;
		n = -n;
	}
	if (neg_flag)
		s = (char*)malloc(sizeof(char) * ft_numlen(n) + 2);
	else
		s = (char*)malloc(sizeof(char) * ft_numlen(n) + 1);
	if (!s)
		return (NULL);
	return (get_num(s, n, neg_flag));
}
