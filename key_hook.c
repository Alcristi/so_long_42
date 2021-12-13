/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:18:14 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/10 15:12:13 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

int	check_collect(int all_collect)
{
	if (all_collect != 0)
		return (0);
	else
		return (1);
}

void	is_grass_row(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	if (key_hook == 'd')
	{
		key = var->game->person_x;
		aux_key = key - 1;
	}
	else if (key_hook == 'a')
	{
		key = var->game->person_x;
		aux_key = key + 1;
	}
	var->map->map[var->game->person_y][key] = 'P';
	var->map->map[var->game->person_y][aux_key] = '0';
	var->game->step++;
	printf("steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_grass_col(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	if (key_hook == 'w')
	{
		key = var->game->person_y;
		aux_key = key + 1;
	}
	else if (key_hook == 's')
	{
		key = var->game->person_y;
		aux_key = key - 1;
	}
	var->map->map[key][var->game->person_x] = 'P';
	var->map->map[aux_key][var->game->person_x] = '0';
	var->game->step++;
	printf("steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_collect_row(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	if (key_hook == 'd')
	{
		key = var->game->person_x;
		aux_key = key - 1;
	}
	else if (key_hook == 'a')
	{
		key = var->game->person_x;
		aux_key = key + 1;
	}
	var->map->map[var->game->person_y][key] = 'P';
	var->map->map[var->game->person_y][aux_key] = '0';
	var->game->all_collect--;
	var->game->step++;
	printf("steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	is_collect_col(t_var *var, int key_hook)
{
	int	key;
	int	aux_key;

	if (key_hook == 'w')
	{
		key = var->game->person_y;
		aux_key = key + 1;
	}
	else if (key_hook == 's')
	{
		key = var->game->person_y;
		aux_key = key - 1;
	}
	var->map->map[key][var->game->person_x] = 'P';
	var->map->map[aux_key][var->game->person_x] = '0';
	var->game->all_collect--;
	var->game->step++;
	printf("steps: %d\n", var->game->step);
	printmap(var->map, var->mlx);
}

void	check_exit_row(t_var *var, int key_hook)
{
	if (check_collect(var->game->all_collect))
	{
		var->game->step++;
		printf("steps: %d\n", var->game->step);
		exit_game(var);
	}
	else
	{
		if (key_hook == 'd')
			var->game->person_x--;
		else
			var->game->person_x++;
	}
}

void	check_exit_col(t_var *var, int keyhook)
{
	if (check_collect(var->game->all_collect))
	{
		exit_game(var);
		var->game->step++;
		printf("steps: %d\n", var->game->step);
	}
	else
	{	
		if (keyhook == 'w')
			var->game->person_y++;
		else
			var->game->person_y--;
	}
}

void	check_keyhook(int keyhook, t_var *var)
{
	if (keyhook == 'd')
		var->game->person_x++;
	else if (keyhook == 'a')
		var->game->person_x--;
	else if (keyhook == 'w')
		var->game->person_y--;
	else if (keyhook == 's')
		var->game->person_y++;
}

void	is_wall(int keyhook, t_var *var)
{
	if (keyhook == 'd')
		var->game->person_x--;
	else if (keyhook == 'a')
		var->game->person_x++;
	else if (keyhook == 'w')
		var->game->person_y++;
	else if (keyhook == 's')
		var->game->person_y--;
}

void	moviment(int keyhook, t_var *var)
{
	check_keyhook(keyhook, var);
	if (keyhook == 'd' || keyhook == 'a')
	{
		if (var->map->map[var->game->person_y][var->game->person_x] == '0')
			is_grass_row(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
			is_collect_row(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
			is_wall(keyhook, var);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
			check_exit_row(var, keyhook);
	}
	else if (keyhook == 'w' || keyhook == 's')
	{
		if (var->map->map[var->game->person_y][var->game->person_x] == '0')
			is_grass_col(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'C')
			is_collect_col(var, keyhook);
		else if (var->map->map[var->game->person_y][var->game->person_x] == '1')
			is_wall(keyhook, var);
		else if (var->map->map[var->game->person_y][var->game->person_x] == 'E')
			check_exit_col(var, keyhook);
	}
}

int	key_hook(int keyhook, t_var *var)
{
	if (keyhook == 65307 || keyhook == 'q')
		exit_game(var);
	else
		moviment(keyhook, var);
	return (0);
}
