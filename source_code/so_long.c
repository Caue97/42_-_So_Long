/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:03:32 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 22:06:56 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game_data	gamedata;

	setbuf(stdout, NULL);
	if (argc == 2)
	{
		gamedata.game_map = generate_map(argv[1]);
		if (validate_map(gamedata.game_map, argv[1]))
		{
			start_game(&gamedata);
			hooks_in_game(&gamedata);
			mlx_loop(gamedata.mlx);
		}
		else
		{
			printf("Error:\nMap invalid for this game!\n");
			free_map(gamedata.game_map);
			exit(1);
		}
	}
	else
	{
		printf("Error:\nYou didn't input a map!\n");
		exit(1);
	}
	return (0);
}

char	**generate_map(char *map_path)
{
	char	**use_map;
	char	*holder_new;
	char	*holder_old;
	char	*full_map;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd <= -1)
		return (NULL);
	full_map = ft_strdup("");
	while (1)
	{
		holder_new = get_next_line(fd);
		if (!holder_new)
			break ;
		holder_old = full_map;
		full_map = ft_strjoin(holder_old, holder_new);
		free_ptr((void *)&holder_old);
		free_ptr((void *)&holder_new);
	}
	use_map = ft_split(full_map, '\n');
	free_ptr((void *)&full_map);
	close(fd);
	return (use_map);
}

void	start_game(t_game_data *game_data)
{
	start_data(game_data);
	start_sprites(game_data);
	start_map(game_data);
}

void	start_data(t_game_data *game_data)
{
	get_window_size(game_data);
	game_data->mlx = mlx_init();
	game_data->window = mlx_new_window(game_data->mlx, game_data->window_width,
			game_data->window_height, "so_long");
	game_data->n_moves = 0;
	game_data->n_collected = 0;
	game_data->collectable = 0;
	game_data->p_direction = 's';
	game_data->game_end = 0;
}

void	start_sprites(t_game_data *game_data)
{
	game_data->sprite_space = start_sprite(IMG_SPACE, game_data);
	game_data->sprite_obstacle = start_sprite(IMG_WALL, game_data);
	game_data->sprite_collectable = start_sprite(IMG_COLLECT, game_data);
	game_data->sprite_goal_off = start_sprite(IMG_GOAL_OFF, game_data);
	game_data->sprite_goal_on = start_sprite(IMG_GOAL_ON, game_data);
	game_data->sprite_player_init = start_sprite(IMG_PLAYER, game_data);
	game_data->s_player_up = start_sprite(PLAYER_UP, game_data);
	game_data->s_player_left = start_sprite(PLAYER_LEFT, game_data);
	game_data->s_player_down = start_sprite(PLAYER_DOWN, game_data);
	game_data->s_player_right = start_sprite(PLAYER_RIGHT, game_data);
}
