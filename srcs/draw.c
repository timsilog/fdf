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

static float	z_bot(float z_min, float z1, float z2)
{
	return ((z1 < z2 ? z1 : z2) - z_min);
}

static void	place_color(t_pic *pic, float x, float y, float z_current)
{
	mlx_pixel_put(pic->mlx, pic->win, x, y,
		get_color(pic, z_current / (pic->z_max - pic->z_min)));
}

static void	driving_axis_x(t_pic *pic, t_3d p1, t_3d p2, float z[2])
{
	float	i;
	float	j;
	int		neg_y;
	float	e;
	float	slope;

	slope = fabs((p2.y - p1.y) / (p2.x - p1.x));
	neg_y = p2.y < p1.y ? 1 : 0;
	i = p1.x;
	j = p1.y;
	e = slope - 1.0;
	while (i <= p2.x)
	{
		place_color(pic, i, j, z[0] ? (1.0 - (i - p1.x) / fabs(p2.x - p1.x)) * 
			z[0] + z_bot(pic->z_min, z[1], z[2]) : z[1]);
		if (e >= 0.0)
		{
			j = neg_y ? j - 1.0 : j + 1.0;
			e -= 1.0;
		}
		i += 1.0;
		e += slope;
	}
}

static void	driving_axis_y(t_pic *pic, t_3d p1, t_3d p2, float z[3])
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
		place_color(pic, i, j, z[0] ? (1.0 - (j - p1.y) / fabs(p2.y - p1.y)) *
			z[0] + z_bot(pic->z_min, z[1], z[2]) : z[1]);
		j += 1.0;
		e += slope;
	}
}

void		draw_line(t_pic *pic, int i1, int i2)
{
	float	dx;
	float	dy;
	float	z_type[3];

	dx = pic->screen[i2].x - pic->screen[i1].x;
	dy = pic->screen[i2].y - pic->screen[i1].y;
	z_type[0] = fabs(pic->points[i2].z - pic->points[i1].z);
	z_type[1] = pic->points[i1].z;
	z_type[2] = pic->points[i2].z;
	//printf("p1: %f, p2: %f\n", pic->points[i1].z, pic->points[i2].z);
	if (fabs(dx) >= fabs(dy))
	{
		if (pic->screen[i2].x >= pic->screen[i1].x)
			driving_axis_x(pic, pic->screen[i1], pic->screen[i2], z_type);
		else
			driving_axis_x(pic, pic->screen[i2], pic->screen[i1], z_type);
	}
	else
	{
		if (pic->screen[i2].y >= pic->screen[i1].y)
			driving_axis_y(pic, pic->screen[i1], pic->screen[i2], z_type);
		else
			driving_axis_y(pic, pic->screen[i2], pic->screen[i1], z_type);
	}
}
