/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:42:42 by tjose             #+#    #+#             */
/*   Updated: 2017/03/22 20:54:28 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			mult_vecmat(t_3d *src, float mat[4][4], t_3d *dest)
{
	float	x;
	float	y;
	float	z;

	x = src->x * mat[0][0] +
		src->y * mat[1][0] +
		src->z * mat[2][0] +
		mat[3][0];
	y = src->x * mat[0][1] +
		src->y * mat[1][1] +
		src->z * mat[2][1] +
		mat[3][1];
	z = src->x * mat[0][2] +
		src->y * mat[1][2] +
		src->z * mat[2][2] +
		mat[3][2];
	dest->x = x;
	dest->y = y;
	dest->z = z;
}

static t_pic	*init_pic(void)
{
	t_pic *pic;

	if (!(pic = malloc(sizeof(t_pic))))
		exit(-1);
	pic->mlx = mlx_init();
	pic->win = mlx_new_window(pic->mlx, WIN_WID, WIN_HEI, "FDF");
	pic->z_min = 0;
	pic->z_max = 0;
	pic->color1 = 0x00ffffff;
	pic->color2 = 0x00ffffff;
	pic->c1.red = 0xff;
	pic->c1.green = 0xff;
	pic->c1.blue = 0xff;
	pic->c2.red = 0xff;
	pic->c2.green = 0xff;
	pic->c2.blue = 0xff;
	pic->x_rot = 0.0;
	pic->y_rot = 0.0;
	pic->scale = 1.0;
	pic->x_move = 0.0;
	pic->y_move = 0.0;
	return (pic);
}

int				main(int argc, char **argv)
{
	t_pic	*pic;

	if (argc < 2 || argc > 4)
	{
		ft_printf("Usage : ./fdf map.fdf [color1 color2]");
		return (-1);
	}
	pic = init_pic();
	parse(pic, argv, argc == 4 ? 1 : 0);
	draw_pic(pic);
	start_loop(pic);
	free(pic);
	return (0);
}
