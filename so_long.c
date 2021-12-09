#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"


static size_t	count_letters(char const *s, char c)
{
	int	amount_of_letters;

	amount_of_letters = 0;
	while (s[amount_of_letters] != c && s[amount_of_letters])
		amount_of_letters++;
	return (amount_of_letters);
}

static size_t	count_words(char const *s, char c)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		total++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (total);
}

static int	ft_abs(int p1, int p2)
{
	if ((p1 - p2) < 0)
		return (p2 - p1);
	return (p1 - p2);
}

char	*ft_substrsplit(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*sub;

	i = 0;
	size = ft_strlen(s);
	if ((ft_strlen(s + 1) < start))
		len = 0;
	if ((ft_strlen(s) + 1) < len + 1)
		sub = (char *)malloc(ft_strlen(s) + 1);
	else if (len == ft_strlen(s))
		sub = (char *)malloc(ft_abs((int)len, (int)start) + 1);
	else
		sub = (char *)malloc(len + 1);
	if ((!s || !sub))
		return (0);
	while ((i < len) && (start + i) < size)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	c_words;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	c_words = count_words(s, c);
	list = malloc(sizeof(char *) * (c_words + 1));
	if (!list)
		return (0);
	while (i < c_words && *s)
	{
		if (*s != c)
		{
			list[i] = ft_substrsplit(s, 0, count_letters(s, c));
			if (!list[i++])
				return (0);
			s += count_letters(s, c);
		}
		else
			s++;
	}
	list[c_words] = NULL;
	return (list);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (to_find[j] && str[j + i] && (to_find[j] == str[j + i])
			&& (j + i) < n)
			j++;
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

// ==============================================================================================================================
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
{   char    **map;
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

//==========================================================================================

int	error(char *msg)
{
	printf("\e[31m\e[1mError\n%s \e[0m \n", msg);
	exit (EXIT_FAILURE);
	return (0);
}

void printmap(t_map *map,t_mlx *mlx)
{
    int i,j,r,s;

    i = 0;
    j = 0;
    while (j < map->height_map)
    {
        while(map->map[j][i])
        {
            if (map ->map[j][i] == '1')
                mlx->img= mlx_xpm_file_to_image(mlx->mlx,"./xpm/img5.xpm",&r,&s);
            else if (map ->map[j][i] == '0')
                mlx->img= mlx_xpm_file_to_image(mlx->mlx,"./xpm/img2.xpm",&r,&s);
            else if (map ->map[j][i] == 'P')    
                mlx->img= mlx_xpm_file_to_image(mlx->mlx,"./xpm/imgfinal.xpm",&r,&s);
            else if (map ->map[j][i] == 'E')
                mlx->img= mlx_xpm_file_to_image(mlx->mlx,"./xpm/Exit.xpm",&r,&s);
            else if (map ->map[j][i] == 'C')
                mlx->img= mlx_xpm_file_to_image(mlx->mlx,"./xpm/pokeball.xpm",&r,&s);
            mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 64*i,64*j);
            mlx_destroy_image(mlx->mlx,mlx->img);
            i++;
        }
        j++;
        i = 0;
    }
}

void check_wall_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(i < map->height_map)
    {
        j = 0;
        while (j < ft_strlen(map->map[i]))
        {
            if (i == 0 || i == map->height_map - 1)
            { 
                if (map->map[i][j] != '1')
                    error("Mapa não está cercado");
            }
            else
            {    
                if (j == 0 || j == ft_strlen(map->map[i]) - 1)
                    if (map->map[i][j] != '1')
                        error("Mapa não está cercado");
            }            
            j++;
        }
        i++;
    }
}

void check_another_map(t_map *map,t_game *game)
{
    int y;
    int x;

    y= 0;
    while(y < map->height_map)
    {
        x = 0;
        if (y > 0)
            if (ft_strlen(map->map[y - 1]) != ft_strlen(map->map[y]))
                error("Não é um retangulo");
        while (x < ft_strlen(map->map[y]))
        {
            if (map->map[y][x] == 'P')
            {
                game->person_x = x;
                game->person_y = y;
                game->amount_person++;
            }
            else if (map->map[y][x] == 'C')
                game->all_collect++;
            else if (map->map[y][x] == 'E')
                game->amount_exit++;  
            if(!ft_strchr("01ECP",map->map[y][x]))
                error("Caracter invalido no mapa");
            x++;
        }
        y++;
    }
    if (game->amount_person != 1)
        error("Há uma quantidade incorreta de start point");
    else if (game->amount_exit != 1)
        error("Há uma quantidade incorreta de saída");
    else if (game->all_collect < 1)
        error("Nenhum coletavel encontrado");

}

void read_map(t_map *map,char *path_map,t_game *game)
{
    char *temp_line;

    map->fd_map = open(path_map,O_RDONLY);
        if (map ->fd_map == -1)
            error("Falha na abertura do arquivo");
    temp_line=get_next_line(map->fd_map);
    if (temp_line == NULL)
        error("Falha na leitura do arquivo");
    map->line_map = ft_strdup("");
    map->height_map = 0;
    while (temp_line)
    {
        map->line_map= ft_strjoin(map->line_map,temp_line);
        free (temp_line);
        map->height_map++;
        temp_line=get_next_line(map->fd_map);
    }
    map->map = ft_split(map->line_map,'\n');
    free (temp_line);
    free(map->line_map);
    check_another_map(map,game);
    check_wall_map(map);
    map->width_map=ft_strlen(map->map[0]);
    // while (i++ < map->height_map)
    //     free(map->map[i]);
    close(map->fd_map);
}

void check_arg_map(t_map *map, int argc, char **argv,t_game *game)
{
    char i;

    i = -1;
    if (argc == 1 || argc > 2)
        error("Quantidade incorreta de argumentos");
    else if (!ft_strnstr(argv[1],".ber",ft_strlen(argv[1])))
        error("Tipo de arquivo invalido");
    else
        read_map(map,argv[1],game);
}

void init_var (t_map *map, t_mlx *mlx,t_game *game)
{
    map->map = NULL;
    map->height_map = 0;
    map->width_map = 0;
    map->fd_map = 0;
    map->line_map = 0;
    //mlx
    mlx->mlx = NULL;
    mlx->win = NULL;
    mlx->img = NULL;
    //game
     game->all_collect = 0;
     game->person_x = 0;
     game->person_y = 0;
     game->amount_person = 0;
     game->amount_exit = 0;
     game->step = 0;
}

int check_collect(int all_collect)
{
    if(all_collect != 0)
        return (0);
    else
        return (1);
}

void exit_game(t_var *var)
{
    int	i;

    i = 0;
    mlx_destroy_window(var->mlx->mlx, var->mlx->win);
    mlx_destroy_display(var->mlx->mlx);
    free(var->mlx->mlx);
    while(i < var->map->height_map)
    {
        free(var->map->map[i]);
        i++;
    }    
    free(var->map->map);
    exit(0);
}

int key_hook(int keyhook, t_var *var)
{
	if(keyhook == 'd')
	{
	    var->game->person_x++;
	    if (var->map->map[var->game->person_y][var->game->person_x] == '0')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y][var->game->person_x - 1] = '0';
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y][var->game->person_x - 1] = '0';
	        var->game->all_collect--;
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
	    {
	        var->game->person_x--;
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
	    {
	        if(check_collect(var->game->all_collect))
	           {
	                var->game->step++;
	                 printf("steps: %d\n",var->game->step);
	                exit_game(var);
	        }
	        else
	            var->game->person_x--;
	    }
	}
	else if (keyhook == 'a')
	{
	
	    var->game->person_x--;
	    if (var->map->map[var->game->person_y][var->game->person_x] == '0')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y][var->game->person_x + 1] = '0';
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y][var->game->person_x + 1] = '0';
	        printf("%d\n",var->game->all_collect);
	        var->game->all_collect--;
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
	    {
	        var->game->person_x++;
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
	    {
	        if(check_collect(var->game->all_collect))
	            {
	                exit_game(var);
	                var->game->step++;
	                printf("steps: %d\n",var->game->step);
	            }
	        else
	            var->game->person_x++;
	    }
	}
	else if (keyhook == 'w')
	{
	
	    var->game->person_y--;
	    if (var->map->map[var->game->person_y][var->game->person_x] == '0')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y + 1][var->game->person_x ] = '0';
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
	    {
	        var->map->map[var->game->person_y][var->game->person_x] = 'P';
	        var->map->map[var->game->person_y + 1][var->game->person_x] = '0';
	        //printf("%d\n",var->game->all_collect);
	        var->game->all_collect--;
	        var->game->step++;
	        printf("steps: %d\n",var->game->step);
	        printmap(var->map,var->mlx);
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
	    {
	        var->game->person_y++;
	    }
	    else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
	    {
	        if(check_collect(var->game->all_collect))
	           {
	                exit_game(var);
	                var->game->step++;
	                printf("steps: %d\n",var->game->step);
	           }
	        else
	            var->game->person_y++;
	    }
	}
    else if (keyhook == 's')
    {
        
        var->game->person_y++;
        if (var->map->map[var->game->person_y][var->game->person_x] == '0')
        {
            var->map->map[var->game->person_y][var->game->person_x] = 'P';
            var->map->map[var->game->person_y - 1][var->game->person_x ] = '0';
            var->game->step++;
            printf("steps: %d\n",var->game->step);
            printmap(var->map,var->mlx);
        }
        else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
        {
            var->map->map[var->game->person_y][var->game->person_x] = 'P';
            var->map->map[var->game->person_y - 1][var->game->person_x] = '0';
           // printf("%d\n",var->game->all_collect);
            var->game->all_collect--;
            var->game->step++;
            printf("steps: %d\n",var->game->step);
            printmap(var->map,var->mlx);
        }
        else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
        {
            var->game->person_y--;
        }
        else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
        {
            if(check_collect(var->game->all_collect))
                {
                    exit_game(var);
                    var->game->step++;
                    printf("steps: %d\n",var->game->step);
                }
            else
                var->game->person_y--;
        }
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;
	t_mlx	mlx;
	t_var	var;

	init_var(&map, &mlx, &game);
	check_arg_map(&map, argc, argv, &game);
	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
		error("Falha na conexão");
	mlx.win = mlx_new_window(mlx.mlx, 64 * map.width_map, 64 * map.height_map,
			"so_long");
	if (mlx.win == NULL)
		error("Falha na criação da janela");
	printmap(&map, &mlx);
	var.mlx = &mlx;
	var.map = &map;
	var.game = &game;
	mlx_key_hook(mlx.win, key_hook, &var);
	mlx_loop(mlx.mlx);
}
