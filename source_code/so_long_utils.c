/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:07:02 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 21:54:21 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

void	get_window_size(t_game_data *game_data)
{
	int	size;

	size = 0;
	game_data->window_width = ft_strlen(game_data->game_map[size]);
	game_data->window_height = 0;
	while (game_data->game_map[size])
	{
		game_data->window_height++;
		size++;
	}
	game_data->window_width *= SPRITE_SIZE;
	game_data->window_height *= SPRITE_SIZE;
}

void	*start_sprite(char *sprite, t_game_data *game_data)
{
	void	*sprite_ptr;

	sprite_ptr = mlx_xpm_file_to_image(game_data->mlx, sprite,
			&game_data->sprite_width, &game_data->sprite_height);
	return (sprite_ptr);
}

void	map_data_init(t_map_data *data)
{
	data->collum = 0;
	data->line = 0;
	data->player_count = 0;
	data->goal_count = 0;
	data->collectable_count = 0;
}

int	display_info(t_game_data *game)
{
	int	map_counter;

	if (DEBUG_INFO)
	{
		map_counter = 0;
		while (game->game_map[map_counter])
		{
			printf("%s\n", game->game_map[map_counter]);
			map_counter++;
		}
		printf("collectable: %d\n", game->collectable);
		printf("collected: %d\n", game->n_collected);
		printf("player: X: %d | Y: %d | D: %c\n",
			game->p_pos_x, game->p_pos_y, ft_toupper(game->p_direction));
	}
	printf("moves: %d\n", game->n_moves);
	return (1);
}
