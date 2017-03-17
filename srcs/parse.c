/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:10:52 by tjose             #+#    #+#             */
/*   Updated: 2017/03/16 19:54:49 by tjose            ###   ########.fr       */
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

static void	parse2(t_pic *pic, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**points;
	int		i;

	i = -1;
	y = 0;
	if (!(pic->points = (t_3d*)malloc(sizeof(t_3d) * pic->size)))
		exit(-1);
	while (get_next_line(fd, &line))
	{
		points = ft_strsplit(line, ' ');
		x = -1;
		while (++x < pic->width)
		{
			pic->points[++i] = get_3d(x, y, ft_atoi(points[x]));
			if (pic->points[i].z < pic->z_min)
				pic->z_min = pic->points[i].z;
			if (pic->points[i].z > pic->z_max)
				pic->z_max = pic->points[i].z;
		}
		y++;
	}
	free(line);
}

static void	parse1(t_pic *pic, int fd)
{
	char	*line;
	char	**points;
	int		width;

	pic->width = 0;
	pic->height = 0;
	while (get_next_line(fd, &line))
	{
		points = ft_strsplit(line, ' ');
		width = 0;
		while (points[width])
			width++;
		if (pic->width != 0 && pic->width != width)
		{
			ft_printf("invalid map");
			exit(-1);
		}
		pic->width = width;
		pic->height++;
	}
	pic->size = pic->width * pic->height;
	free(line);
}

static int	open_file(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_printf("File open error\n");
		exit(0);
	}
	return (fd);
}

void		parse(t_pic *pic, char **argv, int colors)
{
	int		fd;
	int		i;
	float	temp;

	fd = open_file(argv[1]);
	parse1(pic, fd);
	close(fd);
	fd = open_file(argv[1]);
	parse2(pic, fd);
	close(fd);
	if (pic->z_min < 0)
	{
		temp = -pic->z_min;
		i = -1;
		while (++i < pic->size)
			pic->points[i].z += temp;
		pic->z_min += temp;
		pic->z_max += temp;
	}
	if (colors)
	{
		pic->color1 = ft_xtoi(argv[2]);
		pic->color2 = ft_xtoi(argv[3]);
		hex_to_rgb(pic, argv[2], argv[3]);
	}
}
