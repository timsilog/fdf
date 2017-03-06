/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:07:48 by tjose             #+#    #+#             */
/*   Updated: 2017/02/26 20:08:18 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(float xmat[4][4], float ax)
{
	get_id_mat(xmat);
	xmat[1][1] = cos(ax);
	xmat[1][2] = sin(ax);
	xmat[2][1] = -sin(ax);
	xmat[2][2] = cos(ax);
}

static void	rotate_y(float ymat[4][4], float ay)
{
	get_id_mat(ymat);
	ymat[0][0] = cos(ay);
	ymat[0][2] = -sin(ay);
	ymat[2][0] = sin(ay);
	ymat[2][2] = cos(ay);
}

static void	rotate_z(float zmat[4][4], float az)
{
	get_id_mat(zmat);
	zmat[0][0] = cos(az);
	zmat[0][1] = sin(az);
	zmat[1][0] = -sin(az);
	zmat[1][1] = cos(az);
}

void		rotate_mat(float mat[4][4], float ax, float ay, float az)
{
	float	xmat[4][4];
	float	ymat[4][4];
	float	zmat[4][4];
	float	temp1[4][4];
	float	temp2[4][4];

	rotate_x(xmat, ax);
	rotate_y(ymat, ay);
	rotate_z(zmat, az);
	mult_mat(mat, ymat, temp1);
	mult_mat(temp1, xmat, temp2);
	mult_mat(temp2, zmat, mat);
}
