/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:35:31 by tjose             #+#    #+#             */
/*   Updated: 2017/03/17 01:34:40 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	z_bot(t_pic *pic, float z1, float z2)
{
	if (z1 < z2)
		return (pic->z_max - z2);
	else
		return (pic->z_min + z2);
}

static void	place_color(t_pic *pic, float xy[2], float z_current, int flag)
{
	mlx_pixel_put(pic->mlx, pic->win, xy[0], xy[1],
		get_color(pic, z_current / (pic->z_max - pic->z_min), flag));
}

static void	driving_axis_x(t_pic *pic, t_3d p1, t_3d p2, float z[3])
{
	float	ij[2];
	int		neg_y;
	float	e;
	float	slope;

	slope = fabs((p2.y - p1.y) / (p2.x - p1.x));
	neg_y = p2.y < p1.y ? 1 : 0;
	ij[0] = p1.x;
	ij[1] = p1.y;
	e = slope - 1.0;
	while (ij[0] <= p2.x)
	{
		place_color(pic, ij, z[0] ? ((ij[0] - p1.x) / fabs(p2.x - p1.x)) *
				z[0] + z_bot(pic, z[1], z[2]) : z[1], z[1] < z[2] ? 1 : 0);
		if (e >= 0.0)
		{
			ij[1] = neg_y ? ij[1] - 1.0 : ij[1] + 1.0;
			e -= 1.0;
		}
		ij[0] += 1.0;
		e += slope;
	}
}

static void	driving_axis_y(t_pic *pic, t_3d p1, t_3d p2, float z[3])
{
	float	ij[2];
	float	e;
	float	slope;
	int		neg_x;

	slope = fabs((p2.x - p1.x) / (p2.y - p1.y));
	ij[0] = p1.x;
	ij[1] = p1.y;
	neg_x = p2.x < p1.x ? 1 : 0;
	e = (p2.x - p1.x) > 0.0 ? -(1.0 - (p1.x - ij[0]) - (p1.y - ij[1]) *
			((p2.x - p1.x) / (p2.y - p1.y))) : -((p1.x - ij[0]) -
			(p1.y - ij[1]) * ((p2.x - p1.x) / (p2.y - p1.y)));
	while (ij[1] <= p2.y)
	{
		while (e >= 0.0)
		{
			ij[0] = neg_x ? ij[0] - 1.0 : ij[0] + 1.0;
			e -= 1.0;
		}
		place_color(pic, ij, z[0] ? (1.0 - (ij[1] - p1.y) / fabs(p2.y - p1.y)) *
				z[0] + z_bot(pic, z[1], z[2]) : z[1], z[1] < z[2] ? 1 : 0);
		ij[1] += 1.0;
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
	if (fabs(dx) >= fabs(dy))
	{
		if (pic->screen[i2].x >= pic->screen[i1].x)
			driving_axis_x(pic, pic->screen[i1], pic->screen[i2], z_type);
		else
			draw_line(pic, i2, i1);
	}
	else
	{
		if (pic->screen[i2].y >= pic->screen[i1].y)
			driving_axis_y(pic, pic->screen[i1], pic->screen[i2], z_type);
		else
			draw_line(pic, i2, i1);
	}
}
