#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>

int key_press(int keycode, void *param)
{
    if (keycode == 65307) 
    {
        mlx_loop_end(param);

        free(param);
    }
    printf("Key pressed: %d\n", keycode);
    return(0);
}

int close_window(void *param)
{
    mlx_loop_end(param); // Encerra o loop do MiniLibX
    return 0;
}


int main() {
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (mlx == NULL)
    {
        perror("mlx init Failed");
        return (1);
    }

    win = mlx_new_window(mlx, 800, 600, "MiniLibX Window");
    if (win == NULL)
    {
        perror("win_new_windows failed");
        mlx_destroy_display(mlx);
        free(mlx);
        return (1);
    }

    int i = 0 ;
    int j = 0 ;
   
	int	x = 0;
	int	y = 0;
    int	x0 = x;
	int	y0 = y ;
	int color = 000;
	int xtemp = 0;
	int	iteration = 111;
	int	max_iteration = 1000;
	while (i < max_iteration)
	{
		while ( x*x + y*y <= (2*2) && iteration < max_iteration)
		{
			xtemp = x*x - y*y + x0;
			y = 2*x*y + y0;

			x = xtemp;

			iteration = iteration + 1;
		}

		if ( iteration == max_iteration )
		{
			color = 000;
			mlx_pixel_put(mlx, win, x0, y0, color);	
		}
		else
			color = iteration;

		mlx_pixel_put(mlx, win, x0, y0, color);
		j++;
		i++;
	}
    mlx_hook(win, KeyPress, KeyPressMask, key_press, NULL);
    mlx_hook(win, DestroyNotify, NoEventMask, close_window, mlx);
    mlx_loop(mlx);



    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    free(mlx);
    free(win);
    return (0);
}
