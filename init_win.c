#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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
    mlx_loop(mlx);
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    return (0);
}
