/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:11:59 by tjose             #+#    #+#             */
/*   Updated: 2017/03/16 21:29:58 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# define WIN_WID 1920
# define WIN_HEI 1080

typedef struct	s_3d
{
	float		x;
	float		y;
	float		z;
}				t_3d;
typedef struct	s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;
typedef struct	s_pic
{
	t_3d		*points;
	t_3d		*screen;
	int			width;
	int			height;
	int			size;
	int			win_wid;
	int			win_hei;
	void		*mlx;
	void		*win;
	int			color1;
	int			color2;
	t_rgb		c1;
	t_rgb		c2;
	float		z_min;
	float		z_max;
	float		x_rot;
	float		y_rot;
	float		scale;
	float		x_move;
	float		y_move;
}				t_pic;

void			mult_vecmat(t_3d *src, float mat[4][4], t_3d *dest);
void			mult_mat(float m1[4][4], float m2[4][4], float dest[4][4]);
void			translate_mat(float mat[4][4], float x, float y, float z);
void			scale_mat(float mat[4][4], float x, float y, float z);
void			get_id_mat(float mat[4][4]);
void			rotate_mat(float mat[4][4], float ax, float ay, float az);
void			copy_mat(float src[4][4], float dest[4][4]);
void			draw_line(t_pic *pic, int i1, int i2);
void			parse(t_pic *pic, char **argv, int colors);
void			to_alignedview(t_pic *pic);
void			to_worldview(t_pic *pic);
void			get_2d_coord(t_pic *pic);
void			draw_pic(t_pic *pic);
void			hex_to_rgb(t_pic *pic, char *s1, char *s2);
void			start_loop(t_pic *pic);
int				get_color(t_pic *pic, float z, int flag);
int				key_pressed(int keycode, t_pic *pic);

#endif
