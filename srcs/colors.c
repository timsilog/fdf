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

void	hex_to_rgb(t_pic *pic, char *s1, char *s2)
{
	int		i;

	i = ft_strlen(s1) - 1;
	i = i > 1 ? i - 1 : i;
	pic->c1.blue = s1[i] ? ft_xtoi(&s1[i]) : 0;
	s1[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c1.green = s1[i] ? ft_xtoi(&s1[i]) : 0;
	s1[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c1.red = s1[i] ? ft_xtoi(&s1[i]) : 0;
	i = ft_strlen(s2) - 1;
	i = i > 1 ? i - 1 : i;
	pic->c2.blue = s2[i] ? ft_xtoi(&s2[i]) : 0;
	s2[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c2.green = s2[i] ? ft_xtoi(&s2[i]) : 0;
	s2[i--] = '\0';
	i = i > 1 ? i - 1 : i;
	pic->c2.red = s2[i] ? ft_xtoi(&s2[i]) : 0;
}
