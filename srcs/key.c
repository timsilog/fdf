/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:09:50 by tjose             #+#    #+#             */
/*   Updated: 2017/03/22 21:05:17 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	for rotation:
**	w = 13, a = 0, s = 1, d = 2
**
**	for moving:
**	up = 126, left = 123, right = 124, down = 125
**
**	for zooming:
**	q = 12, e = 14
**
**	to exit:
**	esc = 53
*/

int			key_pressed(int keycode, t_pic *pic)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 12 || keycode == 14)
		pic->scale = keycode == 12 ? pic->scale + 0.05 : pic->scale - 0.05;
	if (keycode == 126 || keycode == 125)
		pic->y_move = keycode == 126 ? pic->y_move - .5 : pic->y_move + .5;
	if (keycode == 123 || keycode == 124)
		pic->x_move = keycode == 123 ? pic->x_move - .5 : pic->x_move + .5;
	if (keycode == 13 || keycode == 1)
		pic->x_rot = keycode == 13 ? pic->x_rot + .1 : pic->x_rot - .1;
	if (keycode == 0 || keycode == 2)
		pic->y_rot = keycode == 0 ? pic->y_rot + .1 : pic->y_rot - .1;
	redraw(pic);
	return (0);
}
