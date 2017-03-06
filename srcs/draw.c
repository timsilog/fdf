/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:10:35 by tjose             #+#    #+#             */
/*   Updated: 2017/03/02 17:34:07 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	draw_line(t_pic *pic, t_2d p1, t_2d p2)
{
	float	dx;
	float	dy;
	float	steps;
	float	xinc;
	float	yinc;
	float	i;
	float	x;
	float	y;
	
	x = 0;
	y = 0;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	i = 0;
	while (i < steps)
	{
		x = x + xinc;
		y = y + yinc;
		mlx_pixel_put(pic->mlx, pic->win, x, y, 0x00ffffff);
		i += 1;
	}
}*/

/*float	sign(float n)
{
	if (n > 0)
		return (1.0);
	else if (n < 0)
		return (-1.0);
	else
		return (0);
}

void	draw_line(t_pic *pic, t_2d p1, t_2d p2)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	s1;
	float	s2;
	int		swap;
	float	temp;
	float	d;
	float	i;

	x = p1.x;
	y = p1.y;
	dx = fabs(p2.x - p1.x);
	dy = fabs(p2.y - p1.y);
	s1 = sign(p1.x - p2.x);
	s2 = sign(p1.y - p2.y);
	swap = 0;
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		swap = 1;
	}
	d = 2 * dy - dx;
	i = 0;
	while (i < dx)
	{
		mlx_pixel_put(pic->mlx, pic->win, x, y, 0x0000ff00);
		while (d >= 0)
		{
			d = d - 2 * dx;
			if (swap)
				x = x + s1;
			else
				y = y + s2;
		}
		d = d + 2 * dy;
		if (swap)
			y = y + s2;
		else
			x = x + s1;
		i = i + 1.0;
	}
}*/

void static	driving_axis_x(t_pic *pic, t_2d p1, t_2d p2, float slope)
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
		mlx_pixel_put(pic->mlx, pic->win, i, j, 0x00ff00ff);
		if (e >= 0)
		{
			j = neg_y ? j - 1.0 : j + 1.0;
			e -= 1.0;
		}
		i += 1.0;
		e += slope;
	}
}

void static	driving_axis_y(t_pic *pic, t_2d p1, t_2d p2, float slope)
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
	e = (p2.x - p1.x) > 0 ? -(1 - (p1.x - i) - (p1.y - j) * ((p2.x - p1.x) /
				(p2.y - p1.y))) : -((p1.x - i) - (p1.y - j) * ((p2.x - p1.x) / 
					(p2.y - p1.y)));
	while (j <= p2.y)
	{
		while (e >= 0)
		{
			i = neg_x ? i - 1.0 : i + 1.0;
			e -= 1.0;
		}
		mlx_pixel_put(pic->mlx, pic->win, i, j, 0x0000ff00);
		j += 1;
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
	{
		driving_axis_x(pic, p1, p2, fabs((p2.y - p1.y) / (p2.x - p1.x))
);
	}
	else
	{
		driving_axis_y(pic, p1, p2, fabs((p2.x - p1.x) / (p2.y - p1.y))
);
	}
}
