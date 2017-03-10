/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:14:13 by tjose             #+#    #+#             */
/*   Updated: 2017/03/09 17:48:06 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hex_to_rgb(t_pic *pic, char *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	i = i > 1 ? i - 1 : i;
	pic->c1.blue = s[i] ? ft_xtoi(&s[i]) : 0;
	s[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c1.green = s[i] ? ft_xtoi(&s[i--]) : 0;
	s[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c1.red = s[i] ? ft_xtoi(&s[i]) : 0;
	ft_printf("%d, %d, %d\n", pic->c1.red, pic->c1.green, pic->c1.blue);
}
