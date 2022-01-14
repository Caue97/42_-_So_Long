/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:20:01 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/14 15:35:10 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_direction(int player_direction, t_game_data *g_data)
{
	if (player_direction == W_KEY || player_direction == UP_KEY)
	{
		g_data->p_direction = 'w';
	}
	else if (player_direction == A_KEY || player_direction == LEFT_KEY)
	{
		g_data->p_direction = 'a';
	}
	else if (player_direction == S_KEY || player_direction == DOWN_KEY)
	{
		g_data->p_direction = 's';
	}
	else if (player_direction == D_KEY || player_direction == RIGHT_KEY)
	{
		g_data->p_direction = 'd';
	}
	else
	{
		return ;
	}
}

void	update_player(int keycode, t_game_data *g_data)
{
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		hold_key(g_data, g_data->p_pos_y - 1, g_data->p_pos_x);
	}
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		hold_key(g_data, g_data->p_pos_y, g_data->p_pos_x - 1);
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		hold_key(g_data, g_data->p_pos_y + 1, g_data->p_pos_x);
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		hold_key(g_data, g_data->p_pos_y, g_data->p_pos_x + 1);
	}
	else
	{
		return ;
	}
}

void	hold_key(t_game_data *game_data, int new_y, int new_x)
{
	if (game_data->game_map[new_y][new_x] == '0')
	{
		handle_space(game_data, new_y, new_x);
	}
	else if (game_data->game_map[new_y][new_x] == 'C')
	{
		handle_collectable(game_data, new_y, new_x);
	}
	else if (game_data->game_map[new_y][new_x] == 'E' && \
			(game_data->n_collected == game_data->collectable))
	{
		handle_goal_on(game_data, new_y, new_x);
	}
	else if (game_data->game_map[new_y][new_x] == 'E' && \
			(game_data->n_collected != game_data->collectable))
	{
		handle_goal_off(game_data, new_y, new_x);
	}
	else if (game_data->game_map[new_y][new_x] == '1')
		game_data->n_moves++;
	else
		return ;
}

void	goal_updater(t_game_data *data, int x, int y)
{
	if (data->collectable == data->n_collected)
	{
		sprite_draw(data, data->sprite_goal_on, x, y);
	}
	else if (data->collectable != data->n_collected)
	{
		sprite_draw(data, data->sprite_goal_off, x, y);
	}
}

int	map_resume(t_game_data *game)
{
	int		count_v;
	int		count_h;

	count_v = 0;
	while (game->game_map[count_v])
	{
		count_h = 0;
		while (game->game_map[count_v][count_h])
		{
			if (game->game_map[count_v][count_h] == '1')
				sprite_draw(game, game->sprite_obstacle, count_h, count_v);
			else if (game->game_map[count_v][count_h] == '0')
				sprite_draw(game, game->sprite_space, count_h, count_v);
			else if (game->game_map[count_v][count_h] == 'C')
				sprite_draw(game, game->sprite_collectable, count_h, count_v);
			else if (game->game_map[count_v][count_h] == 'E')
				goal_updater(game, count_h, count_v);
			else if (game->game_map[count_v][count_h] == 'P')
				update_hook_player(game, count_h, count_v);
			count_h++;
		}
		count_v++;
	}
	return (0);
}
