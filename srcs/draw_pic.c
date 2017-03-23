/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:39:00 by tjose             #+#    #+#             */
/*   Updated: 2017/03/22 20:25:55 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_2d_coord(t_pic *pic)
{
	int i;

	i = -1;
	while (++i < pic->size)
	{
		pic->screen[i].x = 11 * pic->screen[i].x + WIN_WID / 2;
		pic->screen[i].y = 11 * pic->screen[i].y + WIN_HEI / 2;
	}
}

static void	to_worldview(t_pic *pic)
{
	float	world[4][4];
	int		i;

	get_id_mat(world);
	translate_mat(world, -(pic->width / 2), -(pic->height / 2), 0);
	rotate_mat(world, 0, 0, .785);
	rotate_mat(world, .785, 0, 0);
	if (!(pic->screen = malloc(sizeof(t_3d) * pic->size)))
		exit(-1);
	i = -1;
	while (++i < pic->size)
		mult_vecmat(&pic->points[i], world, &pic->screen[i]);
}

static void	to_alignedview(t_pic *pic)
{
	float	aligned[4][4];
	int		i;

	get_id_mat(aligned);
	scale_mat(aligned, pic->scale, pic->scale, pic->scale);
	rotate_mat(aligned, pic->x_rot, pic->y_rot, 0);
	translate_mat(aligned, pic->x_move, pic->y_move, 0);
	i = -1;
	while (++i < pic->size)
		mult_vecmat(&pic->screen[i], aligned, &pic->screen[i]);
}

void		draw_pic(t_pic *pic)
{
	int		i;

	to_worldview(pic);
	to_alignedview(pic);
	get_2d_coord(pic);
	i = -1;
	while (++i < pic->size)
	{
		if ((i + 1) % pic->width && (i + 1) < pic->size)
			draw_line(pic, i, i + 1);
		if ((i + pic->width) < pic->size)
			draw_line(pic, i, i + pic->width);
	}
}

void		redraw(t_pic *pic)
{
	mlx_clear_window(pic->mlx, pic->win);
	draw_pic(pic);
}
