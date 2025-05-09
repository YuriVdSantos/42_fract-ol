/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvieira- <yvieira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:35:36 by yvieira-          #+#    #+#             */
/*   Updated: 2025/05/08 20:55:21 by yvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == 65451)
		fractal->max_interaction += 10;
	else if (keysym == 65453)
		fractal->max_interaction -= 10;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	zoom_factor;

	fractal->mouse_re = fractal->shift_x + (x - WIDTH / 2.0)
		/ (WIDTH / (fractal->zoom * 2));
	fractal->mouse_im = fractal->shift_y - (y - HEIGHT / 2.0)
		/ (HEIGHT / (fractal->zoom * 2));
	if (button == Button4)
	{
		zoom_factor = 1.1;
		fractal->zoom *= zoom_factor;
	}
	else if (button == Button5)
	{
		zoom_factor = 1.0 / 1.1;
		fractal->zoom *= zoom_factor;
	}
	else
		return (0);
	fractal->shift_x = fractal->mouse_re - (x - WIDTH / 2.0)
		/ (WIDTH / (fractal->zoom * 2));
	fractal->shift_y = fractal->mouse_im + (y - HEIGHT / 2.0)
		/ (HEIGHT / (fractal->zoom * 2));
	fractal_render(fractal);
	return (0);
}
