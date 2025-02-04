#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data
{
	void	*mlx;
	void	*win;
}				t_data;


int	close_windows(void *param)
{
	mlx_loop_end(param);
	return (0);
}

int	key_press(int keycode, void *param)
{
	if (keycode == 65307)
		mlx_loop_end(param);
	return (0);
}

int	main(void)
{
	t_data	data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FRACTOL");

	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, data.mlx);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_windows, data.mlx);

	mlx_loop(data.mlx);
}