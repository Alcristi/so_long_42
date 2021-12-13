/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:30:00 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/13 17:56:25 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	exit_game(t_var *var)
{
	int	i;

	i = 0;
	mlx_destroy_window(var->mlx->mlx, var->mlx->win);
	mlx_destroy_display(var->mlx->mlx);
	free(var->mlx->mlx);
	while (i < var->map->height_map)
	{
		free(var->map->map[i]);
		i++;
	}
	free(var->map->map);
	exit(0);
}
