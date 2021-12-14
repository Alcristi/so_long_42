/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moviment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:28:54 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/14 00:13:27 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	is_grass_row(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	key = 0;
	aux_key = 0;
	if (key_hook == 'd' || key_hook == 'D')
	{
		key = var->game->person_x;
		aux_key = key - 1;
	}
	else
	{
		key = var->game->person_x;
		aux_key = key + 1;
	}
	var->map->map[var->game->person_y][key] = 'P';
	var->map->map[var->game->person_y][aux_key] = '0';
	var->game->step++;
	printf("Steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_grass_col(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	key = 0;
	aux_key = 0;
	if (key_hook == 'w' || key_hook == 'W')
	{
		key = var->game->person_y;
		aux_key = key + 1;
	}
	else
	{
		key = var->game->person_y;
		aux_key = key - 1;
	}
	var->map->map[key][var->game->person_x] = 'P';
	var->map->map[aux_key][var->game->person_x] = '0';
	var->game->step++;
	printf("Steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_collect_row(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	key = 0;
	aux_key = 0;
	if (key_hook == 'd' || key_hook == 'D')
	{
		key = var->game->person_x;
		aux_key = key - 1;
	}
	else
	{
		key = var->game->person_x;
		aux_key = key + 1;
	}
	var->map->map[var->game->person_y][key] = 'P';
	var->map->map[var->game->person_y][aux_key] = '0';
	var->game->all_collect--;
	var->game->step++;
	printf("Steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_collect_col(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	key = 0;
	aux_key = 0;
	if (key_hook == 'w' || key_hook == 'W')
	{
		key = var->game->person_y;
		aux_key = key + 1;
	}
	else
	{
		key = var->game->person_y;
		aux_key = key - 1;
	}
	var->map->map[key][var->game->person_x] = 'P';
	var->map->map[aux_key][var->game->person_x] = '0';
	var->game->all_collect--;
	var->game->step++;
	printf("Steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_wall(t_var *var, int key_hook)
{
	if (key_hook == 'd' || key_hook == 'D')
		var->game->person_x--;
	else if (key_hook == 'a' || key_hook == 'A')
		var->game->person_x++;
	else if (key_hook == 'w' || key_hook == 'W')
		var->game->person_y++;
	else if (key_hook == 's' || key_hook == 'S')
		var->game->person_y--;
}
