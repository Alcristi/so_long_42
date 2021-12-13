#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../gnl/get_next_line.h"

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    void    *img;
}t_mlx;

typedef struct s_game
{
    int all_collect;
    int person_x;
    int person_y;
    int amount_person;
    int amount_exit;
    int step;
}t_game;

typedef struct s_map
{   
    char    **map;
    int     height_map;
    int     width_map;
    int     fd_map;
    char    *line_map;
}t_map;

typedef struct s_var{
    t_mlx *mlx;
    t_game *game;
    t_map *map;
}t_var;

int exit_game(t_var *var);
void printmap(t_map *map,t_mlx *mlx);
void read_map(t_map *map,char *path_map,t_game *game);
int check_collect(int all_collect);
int key_hook(int keyhook, t_var *var);
void	check_ret(t_map *map);
void check_wall_map(t_map *map);
void check_another_map(t_map *map,t_game *game);
void check_arg_map(t_map *map, int argc, char **argv,t_game *game);
int	error(char *msg);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_substrsplit(char const *s, unsigned int start, size_t len);

