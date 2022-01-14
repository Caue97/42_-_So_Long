/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_hold_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:15:39 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 21:39:16 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_position(char *pos, char *new_pos, char val, char new_val)
{
	*pos = val;
	*new_pos = new_val;
}

void	handle_space(t_game_data *g_data, int new_y, int new_x)
{
	int		past_x;
	int		past_y;

	past_x = g_data->p_pos_x;
	past_y = g_data->p_pos_y;
	if (past_x == g_data->goal_x && past_y == g_data->goal_y)
	{
		change_position(&g_data->game_map[past_y][past_x], \
				&g_data->game_map[new_y][new_x], 'E', 'P');
	}
	else
	{
		change_position(&g_data->game_map[past_y][past_x], \
				&g_data->game_map[new_y][new_x], '0', 'P');
	}
	g_data->n_moves++;
}

void	handle_collectable(t_game_data *g_data, int new_y, int new_x)
{
	int		past_x;
	int		past_y;

	past_x = g_data->p_pos_x;
	past_y = g_data->p_pos_y;
	change_position(&g_data->game_map[past_y][past_x], \
			&g_data->game_map[new_y][new_x], '0', 'P');
	g_data->n_moves++;
	g_data->n_collected++;
}

void	handle_goal_on(t_game_data *g_data, int new_y, int new_x)
{
	int		past_x;
	int		past_y;

	past_x = g_data->p_pos_x;
	past_y = g_data->p_pos_y;
	change_position(&g_data->game_map[past_y][past_x], \
			&g_data->game_map[new_y][new_x], '0', 'E');
	g_data->n_moves++;
	g_data->game_end = 1;
}

void	handle_goal_off(t_game_data *g_data, int new_y, int new_x)
{
	int		past_x;
	int		past_y;

	past_x = g_data->p_pos_x;
	past_y = g_data->p_pos_y;
	change_position(&g_data->game_map[past_y][past_x], \
			&g_data->game_map[new_y][new_x], '0', 'P');
	g_data->n_moves++;
}
