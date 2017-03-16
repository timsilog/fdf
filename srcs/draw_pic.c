/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:39:00 by tjose             #+#    #+#             */
/*   Updated: 2017/03/10 18:59:44 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_pressed(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void		draw_pic(t_pic *pic)
{
	int		i;

	i = -1;
	while (++i < pic->size)
	{
		if ((i + 1) % pic->width && (i + 1) < pic->size)
			draw_line(pic, i, i + 1);
		if ((i + pic->width) < pic->size)
			draw_line(pic, i, i + pic->width);
	}
	mlx_key_hook(pic->win, key_pressed, 0);
	mlx_loop(pic->mlx);
}

void		get_2d_coord(t_pic *pic)
{
	int i;

	i = -1;
	while (++i < pic->size)
	{
		pic->screen[i].x = 11 * pic->screen[i].x + WIN_WID / 2;
		pic->screen[i].y = 11 * pic->screen[i].y + WIN_HEI / 2;
	}
}

void		to_worldview(t_pic *pic)
{
	float	world[4][4];
	int		i;

	get_id_mat(world);
	translate_mat(world, -(pic->width / 2), -(pic->height / 2), 0);
	//scale?
	if (!(pic->screen = malloc(sizeof(t_3d) * pic->size)))
		exit(-1);
	i = -1;
	while (++i < pic->size)
		mult_vecmat(&pic->points[i], world, &pic->screen[i]);
}

void		to_alignedview(t_pic *pic)
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
		mult_vecmat(&pic->screen[i], aligned, &pic->screen[i]);
}
