/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:18:14 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/14 00:09:13 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	moviment(int keyhook, t_var *var)
{
	check_keyhook(var, keyhook);
	if (keyhook == 'd' || keyhook == 'a' || keyhook == 'D' || keyhook == 'A')
	{
		if (var->map->map[var->game->person_y][var->game->person_x] == '0')
			is_grass_row(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
			is_collect_row(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
			is_wall(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
			check_exit_row(var, keyhook);
	}
	else if (keyhook == 'w' || keyhook == 's' || keyhook == 'W'
		|| keyhook == 'S')
	{
		if (var->map->map[var->game->person_y][var->game->person_x] == '0')
			is_grass_col(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
			is_collect_col(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
			is_wall(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
			check_exit_col(var, keyhook);
	}
}

int	key_hook(int keyhook, t_var *var)
{
	if (keyhook == ESC || keyhook == 'q' || keyhook == 'Q')
	{
		if (keyhook == ESC)
			printf("\e[33mO programa foi encerrado com \e[1mESC\e[0m\n");
		else
			printf("\e[33mO programa foi encerrado com \e[1mQ\e[0m\n");
		exit_game(var);
	}
	else
		moviment(keyhook, var);
	return (0);
}
