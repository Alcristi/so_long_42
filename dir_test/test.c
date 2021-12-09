//clang -o test test.c -L -lbsd -L minilibx-linux/ -lm  -lmlx -lXext -lX11
#include "minilibx-linux/mlx.h"
#include <stdlib.h>

typedef struct  s_data{
    void *mlx;
    void *win;
    void *img;
    void *wall;
    void *collect;
    void *person;
    void *exit;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}t_data;

int key_hook(int keycode, t_data *var)
{
    int k,l;
    static int i;
    static int j;
    l = 0;
    if (keycode == 'd')
    {
            mlx_clear_window(var->mlx,var->win);
    while (l < 10)
    {
        k = 0;
        while (k < 10)
        {
            if (k == 0 || k == 9 || l == 0 || l == 9)
                mlx_put_image_to_window(var->mlx, var->win, var->wall, l*i, k*j);
            else
                mlx_put_image_to_window(var->mlx, var->win, var->img, l*i, k*j);
            k++;
        }
        l++;
    }
        if (i != 640 - 64)
            i+=64;
        mlx_put_image_to_window(var->mlx, var->win, var->person,i, j);

    }
    if (keycode == 'a')
    {
            mlx_clear_window(var->mlx,var->win);
        while (l < 10)
    {
        k = 0;
        while (k < 10)
        {
            if (k == 0 || k == 9 || l == 0 || l == 9)
                mlx_put_image_to_window(var->mlx, var->win, var->wall, l*i, k*j);
            else
                mlx_put_image_to_window(var->mlx, var->win, var->img, l*i, k*j);
            k++;
        }
        l++;
    }
        if (i != 0)
            i-=64;
        mlx_put_image_to_window(var->mlx, var->win, var->person,i, j);

    }
    if (keycode == 'w')
    {
            mlx_clear_window(var->mlx,var->win);
        while (l < 10)
    {
        k = 0;
        while (k < 10)
        {
            if (k == 0 || k == 9 || l == 0 || l == 9)
                mlx_put_image_to_window(var->mlx, var->win, var->wall, l*i, k*j);
            else
                mlx_put_image_to_window(var->mlx, var->win, var->img, l*i, k*j);
            k++;
        }
        l++;
    }
        if (j != 0)
            j-=64;
        mlx_put_image_to_window(var->mlx, var->win, var->person,i, j);

    }
    if (keycode == 's')
    {
            mlx_clear_window(var->mlx,var->win);
        while (l < 10)
    {
        k = 0;
        while (k < 10)
        {
            if (k == 0 || k == 9 || l == 0 || l == 9)
                mlx_put_image_to_window(var->mlx, var->win, var->wall, l*i, k*j);
            else
                mlx_put_image_to_window(var->mlx, var->win, var->img, l*i, k*j);
            k++;
        }
        l++;
    }
        if (j != 640 -64)
            j+=64;
        mlx_put_image_to_window(var->mlx, var->win, var->person,i, j);

    }
    return (0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel/8 ));
	*(unsigned int*)dst = color;
}



int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data var;
    int i,j,l,k,b,t,r,s,a,z,o,p;
    int color;

    
    k = 0;
    l = 0;
    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 640, 640, "Hello world!");
    var.img= mlx_xpm_file_to_image(var.mlx,"./xpm/img2.xpm",&i,&j);
    var.person= mlx_xpm_file_to_image(var.mlx,"./xpm/imgfinal.xpm",&b,&t);
    var.wall = mlx_xpm_file_to_image(var.mlx,"./xpm/img5.xpm",&r,&s);
    var.collect = mlx_xpm_file_to_image(var.mlx,"./xpm/pokeball.xpm",&a,&z);
    var.exit = mlx_xpm_file_to_image(var.mlx,"./xpm/Exit.xpm",&o,&p);

   // img.addr = mlx_get_data_addr(img.img,&img.bits_per_pixel,&img.line_length,&img.endian);
    // while (i++ < 100)
    // {
    //     j = 0;
    //     color = i%50 == 0 ? rand() : color;
    //     while (j++ < 100)
    //         my_mlx_pixel_put(&img, i, j, create_trgb(10,5,15,255));
    // }
    
	while (l < 10)
    {
        k = 0;
        while (k < 10)
        {
            if (k == 0 || k == 9 || l == 0 || l == 9)
                mlx_put_image_to_window(var.mlx, var.win, var.wall, l*i, k*j);
            else
                mlx_put_image_to_window(var.mlx, var.win, var.img, l*i, k*j);
            k++;
        }
        l++;
    }
    mlx_put_image_to_window(var.mlx, var.win, var.person, 0, 0);
    mlx_put_image_to_window(var.mlx,var.win,var.collect,128,192);
    mlx_put_image_to_window(var.mlx,var.win,var.exit,192,320);

    mlx_key_hook(var.win,key_hook,&var);
	mlx_loop(var.mlx);

}