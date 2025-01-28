#include <X11/X.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1080
#define HEIGHT 720
#define MAX_INTER 1000

int key_press;

int main ()
{
	void *mlx;
	void *win;
	void *img;

	mlx = mlx_init();
	win = mlx_win(mlx, WIDTH, HEIGHT, "VER COMO ESTA POHA FUNCIONA!!!");
	mlx_loop(data.mlx);

	return 0;
}