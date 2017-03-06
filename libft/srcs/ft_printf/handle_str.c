/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 13:53:41 by tjose             #+#    #+#             */
/*   Updated: 2017/02/22 14:32:12 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*adjust_mbstr(char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if ((j = is_mb(&str[i])))
			i += j;
		else
		{
			str[i] = '\0';
			break ;
		}
	}
	return (str);
}

static char	*adjust_str(t_mods *mods, char *old_str)
{
	char	*new_str;
	int		i;

	if (mods->precision > -1)
	{
		i = -1;
		if (!(new_str = malloc(sizeof(char) * mods->precision + 1)))
			return (NULL);
		while (++i < mods->precision)
			new_str[i] = old_str[i];
		new_str[i] = '\0';
		new_str = adjust_mbstr(new_str);
		mods->precision = -1;
		return (new_str);
	}
	else
		return (old_str);
}

static char	*get_new_str(va_list tags, t_mods *mods)
{
	wchar_t	*old_wstr;
	char	*old_str;
	char	*new_str;

	if (mods->length == l)
	{
		if ((old_wstr = va_arg(tags, wchar_t*)) == NULL)
			new_str = ft_strdup("(null)");
		else
		{
			if (!(new_str = malloc(sizeof(char) * ft_wcslen(old_wstr) + 1)))
				return (NULL);
			ft_wcstombs(new_str, old_wstr, ft_wcslen(old_wstr) + 1);
		}
	}
	else
	{
		if ((old_str = va_arg(tags, char*)) == NULL)
			new_str = ft_strdup("(null)");
		else
			new_str = ft_strdup(old_str);
	}
	if (!(new_str = adjust_str(mods, new_str)))
		return (NULL);
	return (new_str);
}

int			handle_str(va_list tags, t_mods *mods)
{
	char	*ans;
	char	*new_str;
	int		size;

	if (!(new_str = get_new_str(tags, mods)))
		return (-1);
	mods->flags.show_sign = 0;
	mods->flags.show_space = 0;
	mods->flags.hash = 0;
	mods->length = 0;
	size = mods->width < (int)ft_strlen(new_str) ? ft_strlen(new_str) : mods->width;
	if (!(ans = malloc(sizeof(char) * size + 1)))
		return (-1);
	mods->flags.left_justify ? place_left(mods, &ans, size, new_str) :
		place_right(mods, &ans, size, new_str);
	ft_putstr(ans);
	free(new_str);
	free(ans);
	return (size);
}
