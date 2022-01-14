/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:51:27 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 21:53:00 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **game_map)
{
	int	counter;

	if (!game_map)
	{
		return ;
	}
	counter = 0;
	while (game_map[counter])
	{
		free_ptr((void *)&game_map[counter]);
		counter++;
	}
	free_ptr((void *)&game_map);
}

void	free_game(t_game_data *g_data)
{
	mlx_destroy_image(g_data->mlx, g_data->sprite_space);
	mlx_destroy_image(g_data->mlx, g_data->sprite_obstacle);
	mlx_destroy_image(g_data->mlx, g_data->sprite_collectable);
	mlx_destroy_image(g_data->mlx, g_data->sprite_goal_off);
	mlx_destroy_image(g_data->mlx, g_data->sprite_goal_on);
	mlx_destroy_image(g_data->mlx, g_data->sprite_player_init);
	mlx_destroy_image(g_data->mlx, g_data->s_player_up);
	mlx_destroy_image(g_data->mlx, g_data->s_player_left);
	mlx_destroy_image(g_data->mlx, g_data->s_player_down);
	mlx_destroy_image(g_data->mlx, g_data->s_player_right);
	mlx_destroy_window(g_data->mlx, g_data->window);
	mlx_destroy_display(g_data->mlx);
	free_ptr(&g_data->mlx);
}
