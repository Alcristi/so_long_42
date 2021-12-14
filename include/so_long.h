/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:02:17 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/14 00:03:17 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define ESC 65307 

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
}t_mlx;

typedef struct s_game
{
	int	all_collect;
	int	person_x;
	int	person_y;
	int	amount_person;
	int	amount_exit;
	int	step;
}t_game;

typedef struct s_map
{
	char	**map;
	int		height_map;
	int		width_map;
	int		fd_map;
	char	*line_map;
}t_map;

typedef struct s_var{
	t_mlx	*mlx;
	t_game	*game;
	t_map	*map;
}t_var;

int		exit_game(t_var *var);
void	printmap(t_map *map, t_mlx *mlx);
void	read_map(t_map *map, char *path_map, t_game *game);
int		check_collect(int all_collect);
void	check_exit_row(t_var *var, int key_hook);
void	check_exit_col(t_var *var, int key_hook);
void	check_keyhook(t_var *var, int key_hook);
int		key_hook(int keyhook, t_var *var);
void	is_grass_row(t_var *var, int key_hook);
void	is_grass_col(t_var *var, int key_hook);
void	is_collect_row(t_var *var, int key_hook);
void	is_collect_col(t_var *var, int key_hook);
void	is_wall(t_var *var, int key_hook);
void	check_ret(t_map *map);
void	check_wall_map(t_map *map);
void	check_another_map(t_map *map, t_game *game);
void	check_arg_map(t_map *map, int argc, char **argv, t_game *game);
int		error(char *msg);
char	**ft_split_long(char const *s, char c);
#endif