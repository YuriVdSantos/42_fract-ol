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

    // Configurando o hook para eventos de pressionamento de tecla

    int i = 0 ;
    int j = 0 ;
    while(i < 100)
    {
        mlx_pixel_put(mlx, win, (i+100) , (j+100), 159);
        j++;
        i++;
    }
    mlx_hook(win, KeyPress, KeyPressMask, key_press, NULL);
    mlx_hook(win, DestroyNotify, NoEventMask, close_window, mlx);
    mlx_loop(mlx);
<<<<<<< HEAD
=======

    if (keycode == 53)
    {
        mlx_loop_end(mlx);
    }

>>>>>>> cbfae4734a8bfd9093ebd0541dc6771789dbb386
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    free(mlx);
    free(win);
    return (0);
}
