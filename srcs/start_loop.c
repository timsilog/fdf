/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 17:29:13 by tjose             #+#    #+#             */
/*   Updated: 2017/03/22 20:29:42 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	expose_hook(t_pic *pic)
{
	redraw(pic);
	return (0);
}

void		start_loop(t_pic *pic)
{
	mlx_expose_hook(pic->win, expose_hook, pic);
	mlx_key_hook(pic->win, key_pressed, pic);
	mlx_loop(pic->mlx);
}
