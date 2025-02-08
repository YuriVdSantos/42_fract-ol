#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 100

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double  zoom;
    double  offset_x;
    double  offset_y;
    double  x_min;
    double  x_max;
    double  y_min;
    double  y_max;
    int     fractal_type;
    double  cx;
    double  cy; 
}              t_data;

int close_window(void *param)
{
    mlx_loop_end(param);
    return 0;
}

int key_press(int keycode, void *param)
{
    if (keycode == 65307) 
        mlx_loop_end(param);
    return(0);
}

int mandelbrot(double cr, double ci, int max_iter) {
    double zr = 0.0, zi = 0.0;
    int n = 0;

    while (n < max_iter) {
        double zr2 = zr * zr;
        double zi2 = zi * zi;

        if (zr2 + zi2 > 4.0)
            return n;

        zi = 2 * zr * zi + ci;
        zr = zr2 - zi2 + cr;
        n++;
    }

    return max_iter;
}

void calculate_julia(t_data *data, double zx, double zy, int *color) {
    int i = 0;
    double tmp;

    while (i < MAX_ITER) {
        tmp = zx;
        zx = zx * zx - zy * zy + data->cx;
        zy = 2 * zy * tmp + data->cy;
        if (zx * zx + zy * zy >= 4.0)
            break;
        i++;
    }

    *color = (i == MAX_ITER) ? 0x000000 : (0xFFFFFF * i / MAX_ITER);
}

void draw_fractal(t_data *data, char **argv) {
    int py = 0;
    while (py < HEIGHT) 
    {
        int px = 0;
        while (px < WIDTH)
        {
            double cr = data->x_min + (data->x_max - data->x_min) * px / WIDTH;
            double ci = data->y_min + (data->y_max - data->y_min) * py / HEIGHT;
            int color;

            if (data->fractal_type == 0) {
                color = mandelbrot(cr, ci, MAX_ITER);
                color = (color << 21) | (color << 10) | (color << 3);
            } else {
                // data->cx = atof(argv[2]);
                // data->cy = atof(argv[3]);
                calculate_julia(data, cr, ci, &color);
            }

            int pixel = py * data->line_length + px * (data->bits_per_pixel / 8);
            *(int *)(data->addr + pixel) = color;
            px++;
        }
        py++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int mouse_hook(int button, int x, int y, t_data *data, char **argv)
{
    double mouse_re = data->x_min + (data->x_max - data->x_min) * x / WIDTH;
    double mouse_im = data->y_min + (data->y_max - data->y_min) * y / HEIGHT;
    if (button == 4)
    {
        data->zoom *= 0.95;
    }
    else if (button == 5)
    {
        data->zoom *= 1.05;
    }
    double zoom_factor = 1.0 / data->zoom;
    data->x_min = mouse_re - (mouse_re - data->x_min) * zoom_factor;
    data->x_max = mouse_re + (data->x_max - mouse_re) * zoom_factor;
    data->y_min = mouse_im - (mouse_im - data->y_min) * zoom_factor;
    data->y_max = mouse_im + (data->y_max - mouse_im) * zoom_factor;
    draw_fractal(data, argv);
    return (0);
}

int main(int argc, char **argv) {
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Fractal Set");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    data.zoom = 1.0;
    data.x_min = -2.0;
    data.x_max = 1.0;
    data.y_min = -1.5;
    data.y_max = 1.5;
    data.fractal_type = 0; // Default to Mandelbrot

    if (argc == 4 && strcmp(argv[1], "julia") == 0) {
        data.fractal_type = 1;
        data.cx = atof(argv[2]);
        data.cy = atof(argv[3]);
    }

    draw_fractal(&data, argv);

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, KeyPress, KeyPressMask, key_press, data.mlx);
    mlx_mouse_hook(data.win, mouse_hook, &data);
    mlx_hook(data.win, DestroyNotify, NoEventMask, close_window, data.mlx);
    mlx_loop(data.mlx);

    return 0;
}