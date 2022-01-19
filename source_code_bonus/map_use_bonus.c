/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:49:28 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/14 15:20:04 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_map(t_game_data *data)
{
	int		vert_count;
	int		horiz_count;

	vert_count = 0;
	while (data->game_map[vert_count])
	{
		horiz_count = 0;
		while (data->game_map[vert_count][horiz_count])
		{
			if (data->game_map[vert_count][horiz_count] == '1')
				sprite_draw(data, data->sprite_obstacle, horiz_count, \
						vert_count);
			else if (data->game_map[vert_count][horiz_count] == '0')
				sprite_draw(data, data->sprite_space, horiz_count, vert_count);
			else if (data->game_map[vert_count][horiz_count] == 'C')
				map_hook_collet(data, horiz_count, vert_count);
			else if (data->game_map[vert_count][horiz_count] == 'E')
				map_hook_goal(data, horiz_count, vert_count);
			else if (data->game_map[vert_count][horiz_count] == 'P')
				map_hook_player(data, horiz_count, vert_count);
			horiz_count++;
		}
		vert_count++;
	}
}

void	sprite_draw(t_game_data *game, void *sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, sprite, x * SPRITE_SIZE, \
			y * SPRITE_SIZE);
}

void	map_hook_collet(t_game_data *game, int horizontal, int vertical)
{
	sprite_draw(game, game->sprite_collectable, horizontal, vertical);
	game->collectable++;
}

void	map_hook_goal(t_game_data *game, int goal_x, int goal_y)
{
	sprite_draw(game, game->sprite_goal_off, goal_x, goal_y);
	game->goal_x = goal_x;
	game->goal_y = goal_y;
}

void	map_hook_player(t_game_data *game, int player_x, int player_y)
{
	sprite_draw(game, game->sprite_player_init, player_x, player_y);
	game->p_pos_x = player_x;
	game->p_pos_y = player_y;
}
