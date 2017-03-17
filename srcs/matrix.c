/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:13:45 by tjose             #+#    #+#             */
/*   Updated: 2017/03/16 20:29:54 by tjose            ###   ########.fr       */
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

void	scale_mat(float mat[4][4], float x, float y, float z)
{
	float	temp[4][4];
	float	temp2[4][4];

	get_id_mat(temp);
	temp[0][0] = x;
	temp[1][1] = y;
	temp[2][2] = z;
	mult_mat(mat, temp, temp2);
	copy_mat(temp2, mat);
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
