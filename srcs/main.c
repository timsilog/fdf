/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:42:42 by tjose             #+#    #+#             */
/*   Updated: 2017/03/08 17:29:14 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d		get_3d(float x, float y, float z)
{
	t_3d	temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	return (temp);
}

t_2d		get_2d(int x, int y)
{
	t_2d	temp;

	temp.x = x;
	temp.y = y;
	return (temp);
}

t_vertex	*get_vert(float x, float y, float z)
{
	t_vertex *temp;

	temp = (t_vertex*)malloc(sizeof(t_vertex));
	temp->screen = get_2d(0, 0);
	temp->world = get_3d(x, y, z);
	return (temp);
}

t_pic		*init_pic(void)
{
	t_pic *pic;

	if (!(pic = malloc(sizeof(t_pic))))
		exit(-1);
	pic->mlx = mlx_init();
	pic->win = mlx_new_window(pic->mlx, WIN_WID, WIN_HEI, "FDF");
	return (pic);
}

int			main(int argc, char **argv)
{
	t_pic	*pic;
	int		i;//////

	if (argc < 2 || argc > 4 )
	{
		ft_printf("Usage : ./fdf map.fdf [color1 color2]");
		return (-1);
	}
	pic = init_pic();
	parse(pic, argv, argc == 4 ? 1 : 0);
	to_worldview(pic);
	to_alignedview(pic);
	get_2d_coord(pic);
	i = -1;///////
	/*while (++i < pic->size)
	{
		printf("\n%d: x = %f, y = %f, z = %f", i, pic->screen[i].x, pic->screen[i].y, pic->points[i].z);
	}*/
	ft_printf("%x, %x", pic->color1, pic->color2);
	draw_pic(pic);
	free(pic);
	return (0);
}
