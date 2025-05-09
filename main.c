/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvieira- <yvieira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:35:28 by yvieira-          #+#    #+#             */
/*   Updated: 2025/02/10 12:11:52 by yvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	char		*error_message1;
	char		*error_message2;

	error_message1 = "Please enter \n\t\"./fractol mandelbrot\" or";
	error_message2 = "\n\t\"./fractol julia <value_1> <value_2>\"\n";
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx);
	}
	else
	{
		ft_putstr_fd(error_message1, STDERR_FILENO);
		ft_putstr_fd(error_message2, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
