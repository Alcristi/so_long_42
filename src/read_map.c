/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:15:05 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/13 19:25:41 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	read_map(t_map *map, char *path_map, t_game *game)
{
	char	*temp_line;

	map->fd_map = open(path_map, O_RDONLY);
	if (map ->fd_map == -1)
		error("Falha na abertura do arquivo");
	temp_line = get_next_line(map->fd_map);
	if (temp_line == NULL)
		error("Falha na leitura do arquivo");
	map->line_map = ft_strdup("");
	while (temp_line)
	{
		map->line_map = ft_strjoin(map->line_map, temp_line);
		free (temp_line);
		map->height_map++;
		temp_line = get_next_line(map->fd_map);
	}
	map->map = ft_split(map->line_map, '\n');
	free (temp_line);
	free(map->line_map);
	check_ret(map);
	check_wall_map(map);
	check_another_map(map, game);
	map->width_map = ft_strlen(map->map[0]);
	close(map->fd_map);
}

void	load_map(char c, t_mlx *mlx, int i, int j)
{
	int	r;
	int	s;

	r = 0;
	s = 0;
	if (c == '1')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, "./xpm/wall.xpm", &r, &s);
	else if (c == '0')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, "./xpm/grass.xpm", &r, &s);
	else if (c == 'P')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, "./xpm/person.xpm", &r, &s);
	else if (c == 'E')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, "./xpm/Exit.xpm", &r, &s);
	else if (c == 'C')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, "./xpm/ball.xpm", &r, &s);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, r * i, s * j);
	mlx_destroy_image(mlx->mlx, mlx->img);
}

void	printmap(t_map *map, t_mlx *mlx)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->height_map)
	{
		i = 0;
		while (map->map[j][i])
		{
			load_map(map->map[j][i], mlx, i, j);
			i++;
		}
		j++;
	}
}
