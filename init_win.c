#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>

// Definição da função key_press
int key_press(int keycode, void *param) {
    printf("Key pressed: %d\n", keycode);
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
    mlx_hook(win, KeyPress, KeyPressMask, key_press, NULL);

    mlx_loop(mlx);

    if (keycode == 53)
    {
        mlx_loop_end(mlx);
    }

    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    return (0);
}
