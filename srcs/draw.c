/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:35:09 by tjose             #+#    #+#             */
/*   Updated: 2017/03/08 16:24:24 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	driving_axis_x(t_pic *pic, t_2d p1, t_2d p2, float slope)
{
	float	i;
	float	j;
	int		neg_y;
	float	e;

	if (p2.x < p1.x)
		driving_axis_x(pic, p2, p1, slope);
	neg_y = p2.y < p1.y ? 1 : 0;
	i = p1.x;
	j = p1.y;
	e = slope - 1.0;
	while (i <= p2.x)
	{
		mlx_pixel_put(pic->mlx, pic->win, i, j, 16777215);
		if (e >= 0.0)
		{
			j = neg_y ? j - 1.0 : j + 1.0;
			e -= 1.0;
		}
		i += 1.0;
		e += slope;
	}
}

static void	driving_axis_y(t_pic *pic, t_2d p1, t_2d p2, float slope)
{
	float	i;
	int		neg_x;
	float	j;
	float	e;

	if (p2.y < p1.y)
		driving_axis_y(pic, p2, p1, slope);
	i = p1.x;
	j = p1.y;
	neg_x = p2.x < p1.x ? 1 : 0;
	e = (p2.x - p1.x) > 0.0 ? -(1.0 - (p1.x - i) - (p1.y - j) * ((p2.x - p1.x) /
				(p2.y - p1.y))) : -((p1.x - i) - (p1.y - j) *
				((p2.x - p1.x) / (p2.y - p1.y)));
	while (j <= p2.y)
	{
		while (e >= 0.0)
		{
			i = neg_x ? i - 1.0 : i + 1.0;
			e -= 1.0;
		}
		mlx_pixel_put(pic->mlx, pic->win, i, j, 0x0000ff00);
		j += 1.0;
		e += slope;
	}
}

void		draw_line(t_pic *pic, t_2d p1, t_2d p2)
{
	float	dx;
	float	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) >= fabs(dy))
		driving_axis_x(pic, p1, p2, fabs((p2.y - p1.y) / (p2.x - p1.x)));
	else
		driving_axis_y(pic, p1, p2, fabs((p2.x - p1.x) / (p2.y - p1.y)));
}
