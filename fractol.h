/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvieira- <yvieira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:35:41 by yvieira-          #+#    #+#             */
/*   Updated: 2025/05/08 20:55:02 by yvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>

# define WIDTH	800
# define HEIGHT	800

# define BLACK	0x000000
# define WHITE	0xFFFFFF
# define RED		0xFF0000
# define GREEN	0x00FF00
# define BLUE	0x0000FF

# define MAGENTA_BURST		0xFF00FF
# define LIME_SHOCK			0xCCFF00
# define NEON_ORANGE			0xFF6600
# define PSYCHEDELIC_PURPLE	0x660066
# define AQUA_DREAM			0x33CCCC
# define HOT_PINK			0xFF66B2
# define ELECTRIC_BLUE		0x0066FF
# define LAVA_RED			0xFF3300

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
}		t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx;
	void	*win_ptr;
	t_img	img;
	double	escape_value;
	int		max_interaction;
	double	zoom;
	double	shift_x;
	double	shift_y;
	double	julia_x;
	double	julia_y;
	double	x_min;
	double	x_max;
	double	y_max;
	double	y_min;
	double	mouse_re;
	double	mouse_im;
}		t_fractal;

int			ft_strncmp(char *s1, char *s2, int n);
void		ft_putstr_fd(char *s, int fd);
double		atodbl(char *s);
void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
double		map(int pixel, double min, double max, int size);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
void		data_init(t_fractal *fractal);

#endif