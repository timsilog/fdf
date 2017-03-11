/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:35:31 by tjose             #+#    #+#             */
/*   Updated: 2017/03/10 18:59:41 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	place_color(t_pic *pic, float x, float y, float z_current)
{
	mlx_pixel_put(pic->mlx, pic->win, x, y, get_color(pic, z_current / (pic->z_max - pic->z_min)));
	//ft_printf("%d\n", get_color(pic, z_current / (pic->z_max - pic->z_min)));
}

static void	driving_axis_x(t_pic *pic, t_2d p1, t_2d p2, float z)
{
	float	i;
	float	j;
	int		neg_y;
	float	e;
	float	slope;

	slope = fabs((p2.y - p1.y) / (p2.x - p1.x));
	if (p2.x < p1.x)
		driving_axis_x(pic, p2, p1, slope);
	neg_y = p2.y < p1.y ? 1 : 0;
	i = p1.x;
	j = p1.y;
	e = slope - 1.0;
	while (i <= p2.x)
	{
		place_color(pic, i, j, (i - p1.x) / fabs(p2.x - p1.x) * z);
		if (e >= 0.0)
		{
			j = neg_y ? j - 1.0 : j + 1.0;
			e -= 1.0;
		}
		i += 1.0;
		e += slope;
	}
}

static void	driving_axis_y(t_pic *pic, t_2d p1, t_2d p2, float z)
{
	float	i;
	float	j;
	float	e;
	float	slope;
	int		neg_x;

	slope = fabs((p2.x - p1.x) / (p2.y - p1.y));
	i = p1.x;
	j = p1.y;
	neg_x = p2.x < p1.x ? 1 : 0;
	e = (p2.x - p1.x) > 0.0 ? -(1.0 - (p1.x - i) - (p1.y - j) * ((p2.x - p1.x) /
				(p2.y - p1.y))) : -((p1.x - i) - (p1.y - j) * ((p2.x - p1.x) /
				(p2.y - p1.y)));
	while (j <= p2.y)
	{
		while (e >= 0.0)
		{
			i = neg_x ? i - 1.0 : i + 1.0;
			e -= 1.0;
		}
		place_color(pic, i, j, (j - p1.y) / fabs(p2.y - p1.y) * z);
		j += 1.0;
		e += slope;
	}
}

void		draw_line(t_pic *pic, int i1, int i2)
{
	t_2d	p1;
	t_2d	p2;
	float	dx;
	float	dy;
	float	z_diff;

	p1 = pic->screen[i1];
	p2 = pic->screen[i2];
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	z_diff = fabs(pic->points[i2].z - pic->points[i1].z);
	if (fabs(dx) >= fabs(dy))
	{
		if (p2.x >= p1.x)
			driving_axis_x(pic, p1, p2, z_diff ? z_diff : pic->points[i1].z);
		else
			driving_axis_x(pic, p2, p1, z_diff ? z_diff : pic->points[i1].z);
	}
	else
	{
		if (p2.y >= p1.y)
			driving_axis_y(pic, p1, p2, z_diff ? z_diff : pic->points[i1].z);
		else
			driving_axis_y(pic, p2, p1, z_diff ? z_diff : pic->points[i1].z);
	}
}
