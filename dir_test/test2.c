#include "minilibx-linux/mlx.h"
#include <stdio.h>

typedef struct s_vars{
    void    *mlx;
    void    *win;
}t_vars;

int key_hook(unsigned int keycode, char *str)
{
    printf("%x\n",keycode);
    return (0);
}

int main ()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world");

    mlx_key_hook(vars.win,key_hook,"oi");
    
    mlx_loop(vars.mlx);
}


