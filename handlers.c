#include "fractol.h"
#include "mlx.h"
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
		fractal->shift_y += (0.5 *fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_plus)
		fractal->max_interaction += 10;
	else if (keysym == XK_minus)
		fractal->max_interaction -= 10;
	fractal_render(fractal);
	return (0);
}

int mouse_handler(int button, int x, int y, t_fractal *fractal)
{
    double mouse_re = fractal->shift_x + (x - WIDTH / 2.0) / (WIDTH / (fractal->zoom * 2));
    double mouse_im = fractal->shift_y - (y - HEIGHT / 2.0) / (HEIGHT / (fractal->zoom * 2));

    double zoom_factor;
    if (button == Button4) {
        zoom_factor = 1.1; 
        fractal->zoom *= zoom_factor;
    } else if (button == Button5) {
        zoom_factor = 1.0 / 1.1; 
        fractal->zoom *= zoom_factor;
    } else {
        return 0; 
    }
    fractal->shift_x = mouse_re - (x - WIDTH / 2.0) / (WIDTH / (fractal->zoom * 2));
    fractal->shift_y = mouse_im + (y - HEIGHT / 2.0) / (HEIGHT / (fractal->zoom * 2));

    fractal_render(fractal);
    return 0;
}

int	julia_track(int x, int y, t_fractal *fractal)
{
    if(!ft_strncmp(fractal->name, "julia", 5))
    {
        fractal->julia_x = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
        fractal->julia_y = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
        fractal_render(fractal);
    }
    return (0);
}


// int mouse_handler(int button, t_fractal *fractal)
// {
// 	if (button == Button5)
// 		fractal->zoom *= 0.95;
// 	else if (button == Button4)
// 		fractal->zoom *= 1.05;
// 	fractal_render(fractal);
// 	return 0;
// }
