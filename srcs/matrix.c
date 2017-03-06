/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:13:45 by tjose             #+#    #+#             */
/*   Updated: 2017/02/28 15:14:36 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_id_mat(float mat[4][4])
{
	ft_bzero(mat[0], sizeof(float) * 4);
	ft_bzero(mat[1], sizeof(float) * 4);
	ft_bzero(mat[2], sizeof(float) * 4);
	ft_bzero(mat[3], sizeof(float) * 4);
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
}

void	mult_mat(float m1[4][4], float m2[4][4], float dest[4][4])
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			dest[i][j] = m1[i][0] * m2[0][j] +
				m1[i][1] * m2[1][j] +
				m1[i][2] * m2[2][j] +
				m1[i][3] * m2[3][j];
		}
	}
}

void	translate_mat(float mat[4][4], float x, float y, float z)
{
	float	temp[4][4];
	float	temp2[4][4];

	get_id_mat(temp);
	temp[3][0] = x;
	temp[3][1] = y;
	temp[3][2] = z;
	mult_mat(mat, temp, temp2);
	copy_mat(temp2, mat);
}

//do i still need this?
void	copy_mat(float src[4][4], float dest[4][4])
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dest[i][j] = src[i][j];
	}
}

void	mult_vecmat(t_3d *src, float mat[4][4], t_3d *dest)
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
