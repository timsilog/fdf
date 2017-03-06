/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 14:15:06 by tjose             #+#    #+#             */
/*   Updated: 2017/02/07 14:43:01 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	adjust_nmods(t_mods *mods, char c, intmax_t n)
{
	if (c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
	{
		mods->flags.show_sign = 0;
		mods->flags.show_space = 0;
	}
	if (n == 0 && (c == 'x' || c == 'X'))
		mods->flags.hash = 0;
	if (mods->flags.hash == yes)
	{
		if (c == 'o')
			mods->flags.hash = o;
		if (c == 'x' || c == 'p')
			mods->flags.hash = x;
		if (c == 'X')
			mods->flags.hash = X;
	}
}

static char	*ito_specifier(intmax_t n, t_mods *mods, int u_flag)
{
	char	*ans;
	char	c;
	int		i;

	c = mods->specifier;
	if (c == 'u' || c == 'd' || c == 'i')
		ans = u_flag ? ft_uitoabase(n, 10) : ft_itoa(n);
	else if (c == 'o')
		ans = ft_uitoabase(n, 8);
	else if (c == 'x' || c == 'X' || c == 'p')
	{
		i = -1;
		ans = ft_uitoabase(n, 16);
		while ((c == 'x' || c == 'p') && ans[++i])
		{
			if (ans[i] >= 'A' && ans[i] <= 'Z')
				ans[i] += 32;
		}
	}
	else
		return (NULL);
	if (n == 0 && mods->precision == 0)
		ans[0] = '\0';
	return (ans);
}

char		*convert_ulength(va_list tags, t_mods *mods, char c)
{
	uintmax_t n;

	n = va_arg(tags, uintmax_t);
	adjust_nmods(mods, c, n);
	if (mods->length == hh)
		return (ito_specifier((unsigned char)n, mods, 1));
	else if (mods->length == h)
		return (ito_specifier((unsigned short)n, mods, 1));
	else if (mods->length == l)
		return (ito_specifier((unsigned long)n, mods, 1));
	else if (mods->length == ll)
		return (ito_specifier((unsigned long long)n, mods, 1));
	else if (mods->length == j)
		return (ito_specifier((uintmax_t)n, mods, 1));
	else if (mods->length == z)
		return (ito_specifier((ssize_t)n, mods, 1));
	else
		return (ito_specifier((unsigned int)n, mods, 1));
}

static char	*check_neg(intmax_t n, t_mods *mods)
{
	char *temp;

	if (mods->length == l)
		temp = (n < 0) ? ito_specifier((long)-n, mods, 1) :
			ito_specifier((long)n, mods, 1);
	else if (mods->length == ll)
		temp = (n < 0) ? ito_specifier((long long)-n, mods, 1) :
			ito_specifier((long long)n, mods, 1);
	else if (mods->length == j)
		temp = (n < 0) ? ito_specifier(-n, mods, 1) :
			ito_specifier(n, mods, 1);
	else if (mods->length == z)
		temp = (n < 0) ? ito_specifier((size_t)-n, mods, 1) :
			ito_specifier((size_t)n, mods, 1);
	if (n < 0)
		return (ft_strjoin("-", temp));
	return (temp);
}

char		*convert_length(va_list tags, t_mods *mods, char c)
{
	intmax_t	n;

	n = va_arg(tags, intmax_t);
	adjust_nmods(mods, c, n);
	if (mods->length == hh)
		return (ito_specifier((char)n, mods, 0));
	else if (mods->length == h)
		return (ito_specifier((short)n, mods, 0));
	else if (mods->length == l || mods->length == ll || mods->length == j
			|| mods->length == z)
		return (check_neg(n, mods));
	return (ito_specifier((int)n, mods, 0));
}
