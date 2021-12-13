/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:34:53 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/10 02:59:13 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_var(t_map *map, t_mlx *mlx, t_game *game)
{
	map->map = NULL;
	map->height_map = 0;
	map->width_map = 0;
	map->fd_map = 0;
	map->line_map = 0;
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	game->all_collect = 0;
	game->person_x = 0;
	game->person_y = 0;
	game->amount_person = 0;
	game->amount_exit = 0;
	game->step = 0;
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
	mlx_hook(var.mlx->win, 17, 1L << 0, exit_game, &var);
	mlx_loop(mlx.mlx);
}
