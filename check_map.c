/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:20 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/13 17:30:32 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_wall_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height_map)
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

void	check_ret(t_map *map)
{
	int	i;

	i = 1;
	while (i < map->height_map)
	{
		if (ft_strlen(map->map[i - 1]) != ft_strlen(map->map[i]))
			error("Não é um retangulo");
		i++;
	}
}

void	check_rules_game(t_game *game)
{
	if (game->amount_person != 1)
		error("Há uma quantidade incorreta de start point");
	else if (game->amount_exit != 1)
		error("Há uma quantidade incorreta de saída");
	else if (game->all_collect < 1)
		error("Nenhum coletavel encontrado");
}

void	check_another_map(t_map *map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height_map)
	{
		x = 0;
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
			if (!ft_strchr("01ECP", map->map[y][x++]))
				error("Caracter invalido no mapa");
		}
		y++;
	}
	check_rules_game(game);
}

void	check_arg_map(t_map *map, int argc, char **argv, t_game *game)
{
	int	i;

	i = -1;
	if (argc == 1 || argc > 2)
		error("Quantidade incorreta de argumentos");
	else if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		error("Tipo de arquivo invalido");
	else
		read_map(map, argv[1], game);
}
