#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 500 // Reduzido para melhor performance

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double  zoom;
    double  x_min;
    double  x_max;
    double  y_min;
    double  y_max;
} t_data;

int close_window(void *param) {
    mlx_loop_end(param);
    return 0;
}

int key_press(int keycode, void *param) {
    if (keycode == 65307) {
        mlx_loop_end(param);
    }
    return 0;
}

int mandelbrot(double cr, double ci, int max_iter) {
    double zr = 0.0, zi = 0.0;
    int n = 0;

    while (n < max_iter) {
        double zr2 = zr * zr;
        double zi2 = zi * zi;

        if (zr2 + zi2 > 4.0) return n;

        zi = 2 * zr * zi + ci;
        zr = zr2 - zi2 + cr;
        n++;
    }
    return max_iter;
}

void draw_mandelbrot(t_data *data) {
    for (int py = 0; py < HEIGHT; py++) {
        for (int px = 0; px < WIDTH; px++) {
            double cr = data->x_min + (data->x_max - data->x_min) * px / WIDTH;
            double ci = data->y_min + (data->y_max - data->y_min) * py / HEIGHT;

            int color = mandelbrot(cr, ci, MAX_ITER);
            int pixel_color = (color << 21) | (color << 10) | (color << 3);

            int pixel = py * data->line_length + px * (data->bits_per_pixel / 8);
            *(int *)(data->addr + pixel) = pixel_color;
        }
    }
}

int mouse_hook(int button, int x, int y, t_data *data) {
    double mouse_re = data->x_min + (data->x_max - data->x_min) * x / WIDTH;
    double mouse_im = data->y_min + (data->y_max - data->y_min) * y / HEIGHT;

    if (button == 4) {
        data->zoom *= 1.1;
    } else if (button == 5) {
        data->zoom /= 1.1;
    }

    double zoom_factor = 1.0 / data->zoom;

    // Atualiza as coordenadas
    data->x_min = mouse_re - (mouse_re - data->x_min) * zoom_factor;
    data->x_max = mouse_re + (data->x_max - mouse_re) * zoom_factor;
    data->y_min = mouse_im - (mouse_im - data->y_min) * zoom_factor;
    data->y_max = mouse_im + (data->y_max - mouse_im) * zoom_factor;

    draw_mandelbrot(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}

int main(void) {
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot Set");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    data.zoom = 1.0;
    data.x_min = -2.0;
    data.x_max = 1.0;
    data.y_min = -1.5;
    data.y_max = 1.5;

    draw_mandelbrot(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

    mlx_hook(data.win, KeyPress, KeyPressMask, key_press, data.mlx);
    mlx_mouse_hook(data.win, mouse_hook, &data);
    mlx_hook(data.win, DestroyNotify, NoEventMask, close_window, data.mlx);
    
    mlx_loop(data.mlx);
    return 0;
}