/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:27:31 by tjose             #+#    #+#             */
/*   Updated: 2017/02/22 14:35:11 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_mods(t_mods *mods)
{
	mods->flags.left_justify = 0;
	mods->flags.show_sign = 0;
	mods->flags.show_space = 0;
	mods->flags.hash = no;
	mods->flags.fill_zeroes = 0;
	mods->width = 0;
	mods->precision = -1;
	mods->length = none;
	mods->specifier = '\0';
}

static int	find_mods(int i, const char *format, t_mods *mods, va_list tags)
{
	while (format[i])
	{
		if (format[i] == '-' || format[i] == '+' || format[i] == ' '
				|| format[i] == '#' || format[i] == '0')
			i += handle_flags(&format[i], mods);
		else if (format[i] == '*' || ft_isdigit(format[i]))
			i += handle_width(&format[i], mods, tags);
		else if (format[i] == '.')
			i += handle_precision(&format[i], mods, tags);
		else if (format[i] == 'h' || format[i] == 'l' ||
				format[i] == 'j' || format[i] == 'z')
			i += handle_length(&format[i], mods);
		else if (format[i])
		{
			i += handle_specifier(format[i], mods);
			break ;
		}
		else
			break ;
	}
	return (i);
}

static int	find_handle(va_list tags, t_mods *mods)
{
	char c;

	c = mods->specifier;
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'x' || c == 'X' || c == 'p')
		return (handle_number(tags, mods));
	else if (c == 'c')
		return (handle_char(tags, mods));
	else if (c == 's')
		return (handle_str(tags, mods));
	else if (mods->specifier)
		return (handle_nospec(mods));
	return (0);
}

static int	print_string(const char *format, int count,
		t_mods mods, va_list tags)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (format[i])
	{
		if ((temp = ft_strchr(&format[i], '%')))
		{
			write(1, &format[i], temp - &format[i]);
			count += temp - &format[i];
			init_mods(&mods);
			i = find_mods(i + temp - &format[i] + 1, format, &mods, tags);
			if ((j = find_handle(tags, &mods)) < 0)
				return (-1);
			count += j;
		}
		else
		{
			ft_putstr(&format[i]);
			count += ft_strlen(&format[i]);
			break ;
		}
	}
	return (count);
}

int			ft_printf(const char *format, ...)
{
	va_list	tags;
	int		count;
	t_mods	mods;

	if (!format)
		return (0);
	va_start(tags, format);
	count = 0;
	init_mods(&mods);
	if ((count = print_string(format, count, mods, tags)) < 0)
		return (-1);
	return (count);
}
