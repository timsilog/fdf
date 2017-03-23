/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:14:13 by tjose             #+#    #+#             */
/*   Updated: 2017/03/22 20:56:01 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hex_to_rgb(t_pic *pic, char *s1, char *s2)
{
	int		i;

	i = ft_strlen(s1) - 1;
	i = i >= 1 ? i - 1 : i;
	pic->c1.blue = i > -1 ? ft_xtoi(&s1[i]) : 0;
	s1[i--] = '\0';
	i = i >= 1 ? i - 1 : i;
	pic->c1.green = i > -1 ? ft_xtoi(&s1[i]) : 0;
	s1[i--] = '\0';
	i = i >= 1 ? i - 1 : i;
	pic->c1.red = i > -1 ? ft_xtoi(&s1[i]) : 0;
	i = ft_strlen(s2) - 1;
	i = i >= 1 ? i - 1 : i;
	pic->c2.blue = i > -1 ? ft_xtoi(&s2[i]) : 0;
	s2[i--] = '\0';
	i = i >= 1 ? i - 1 : i;
	pic->c2.green = i > -1 ? ft_xtoi(&s2[i]) : 0;
	s2[i--] = '\0';
	i = i >= 1 ? i - 1 : i;
	pic->c2.red = i > -1 ? ft_xtoi(&s2[i]) : 0;
}

/*
**	z is a percentage of how high or low the current pixel is on our z spectrum
*/

int		get_color(t_pic *pic, float z, int flag)
{
	int		r;
	int		g;
	int		b;

	r = round(abs(pic->c2.red - pic->c1.red) * z);
	if (flag)
		r = pic->c1.red < pic->c2.red ? r + pic->c1.red : pic->c1.red - r;
	else
		r = pic->c2.red < pic->c1.red ? r + pic->c2.red : pic->c2.red - r;
	g = round(abs(pic->c2.green - pic->c1.green) * z);
	if (flag)
		g = pic->c1.green < pic->c2.green ? g + pic->c1.green :
			pic->c1.green - g;
	else
		g = pic->c2.green < pic->c1.green ? g + pic->c2.green :
			pic->c2.green - g;
	b = round(abs(pic->c2.blue - pic->c1.blue) * z);
	if (flag)
		b = pic->c1.blue < pic->c2.blue ? b + pic->c1.blue : pic->c1.blue - b;
	else
		b = pic->c2.blue < pic->c1.blue ? b + pic->c2.blue : pic->c2.blue - b;
	return ((r * 0x10000) + (g * 0x100) + b);
}
