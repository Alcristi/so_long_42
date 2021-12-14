/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:28:50 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/14 00:11:18 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_collect(int all_collect)
{
	if (all_collect != 0)
		return (0);
	else
		return (1);
}

void	check_exit_row(t_var *var, int key_hook)
{
	if (check_collect(var->game->all_collect))
	{
		var->game->step++;
		printf("Steps: %d\n", var->game->step);
		printf("\e[32m\e[1mParabéns você ganhou\e[0m\n");
		exit_game(var);
	}
	else
	{
		if (key_hook == 'd' || key_hook == 'D')
			var->game->person_x--;
		else
			var->game->person_x++;
		printf("\e[34m\e[1mPor favor, colete todos os coletaveis\e[0m\n");
	}
}

void	check_exit_col(t_var *var, int key_hook)
{
	if (check_collect(var->game->all_collect))
	{
		var->game->step++;
		printf("Steps: %d\n", var->game->step);
		printf("\e[32m\e[1mParabéns você ganhou\e[0m\n");
		exit_game(var);
	}
	else
	{	
		if (key_hook == 'w' || key_hook == 'W')
			var->game->person_y++;
		else
			var->game->person_y--;
		printf("\e[34m\e[1mPor favor, colete todos os coletaveis\e[0m\n");
	}
}

void	check_keyhook(t_var *var, int key_hook)
{
	if (key_hook == 'd' || key_hook == 'D')
		var->game->person_x++;
	else if (key_hook == 'a' || key_hook == 'A')
		var->game->person_x--;
	else if (key_hook == 'w' || key_hook == 'W')
		var->game->person_y--;
	else if (key_hook == 's' || key_hook == 'S')
		var->game->person_y++;
}
