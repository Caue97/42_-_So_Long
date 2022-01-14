/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:42:17 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/14 15:34:30 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hooks_in_game(t_game_data *g_data)
{
	mlx_hook(g_data->window, EVT_KEY_PRESS, 1L << 0, &key_press, g_data);
	mlx_hook(g_data->window, EVT_DESTROY_NOTIFY, 0, &quit_game, g_data);
	mlx_hook(g_data->window, EVT_FOCUS, 1L << 21, &map_resume, g_data);
}

int	key_press(int key_pressed, t_game_data *game_data)
{
	if (key_pressed == ESC_KEY || key_pressed == Q_KEY)
	{
		quit_game(game_data);
	}
	else if (game_data->game_end)
	{
		return (0);
	}
	else
	{
		map_update(key_pressed, game_data);
		display_info(game_data);
	}
	return (0);
}

int	quit_game(t_game_data *game_data)
{
	free_map(game_data->game_map);
	free_game(game_data);
	exit(0);
	return (0);
}

void	map_update(int keycode, t_game_data *game_data)
{
	update_direction(keycode, game_data);
	update_player(keycode, game_data);
	map_updater(game_data);
}

void	map_updater(t_game_data *data)
{
	int		count_v;
	int		count_h;

	count_v = 0;
	while (data->game_map[count_v])
	{
		count_h = 0;
		while (data->game_map[count_v][count_h])
		{
			if (data->game_map[count_v][count_h] == '1')
				sprite_draw(data, data->sprite_obstacle, count_h, count_v);
			else if (data->game_map[count_v][count_h] == '0')
				sprite_draw(data, data->sprite_space, count_h, count_v);
			else if (data->game_map[count_v][count_h] == 'C')
				sprite_draw(data, data->sprite_collectable, count_h, count_v);
			else if (data->game_map[count_v][count_h] == 'E')
				goal_updater(data, count_h, count_v);
			else if (data->game_map[count_v][count_h] == 'P')
				update_hook_player(data, count_h, count_v);
			count_h++;
		}
		count_v++;
	}
}
