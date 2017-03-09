/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:39:00 by tjose             #+#    #+#             */
/*   Updated: 2017/03/08 15:22:40 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pic(t_pic *pic)
{
	int		i;

	i = -1;
	while (++i < pic->size)
	{
		mlx_pixel_put(pic->mlx, pic->win, pic->screen[i].x, pic->screen[i].y, 0x00ffffff);
		if ((i + 1) % pic->width && (i + 1) < pic->size)
			draw_line(pic, pic->screen[i], pic->screen[i + 1]);
		if ((i + pic->width) < pic->size)
			draw_line(pic, pic->screen[i], pic->screen[i + pic->width]);
	}
	mlx_loop(pic->mlx);
}

void	get_2d_coord(t_pic *pic)
{
	int i;

	if (!(pic->screen = malloc(sizeof(t_2d) * pic->size)))
		exit(-1);
	i = -1;
	while (++i < pic->size)
	{
		if (!pic->points[i].z)
			pic->points[i].z = 1;
		pic->screen[i].x = 11 * pic->points[i].x + WIN_WID / 2;
		pic->screen[i].y = 11 * pic->points[i].y + WIN_HEI / 2;
	}
}

void	to_worldview(t_pic *pic)
{
	float	world[4][4];
	int		i;

	get_id_mat(world);
	translate_mat(world, -(pic->width / 2), -(pic->height / 2), 0);
	//scale?
	i = -1;
	while (++i < pic->size)
		mult_vecmat(&pic->points[i], world, &pic->points[i]);
}

void	to_alignedview(t_pic *pic)
{
	float	aligned[4][4];
	int		i;

	get_id_mat(aligned);
	rotate_mat(aligned, 0, 0, .785);
	rotate_mat(aligned, .785, 0, 0);
	//scale here?
	//translate_mat(aligned, 0, 0, 0);??
	i = -1;
	while (++i < pic->size)
		mult_vecmat(&pic->points[i], aligned, &pic->points[i]);
}
