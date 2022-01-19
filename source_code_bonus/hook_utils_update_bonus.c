/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:36:50 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/14 15:47:13 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_hook_player(t_game_data *g_data, int player_x, int player_y)
{
	if (g_data->p_direction == 'w')
	{
		sprite_draw(g_data, g_data->s_player_up, player_x, player_y);
	}
	else if (g_data->p_direction == 'a')
	{
		sprite_draw(g_data, g_data->s_player_left, player_x, player_y);
	}
	else if (g_data->p_direction == 's')
	{
		sprite_draw(g_data, g_data->s_player_down, player_x, player_y);
	}
	else if (g_data->p_direction == 'd')
	{
		sprite_draw(g_data, g_data->s_player_right, player_x, player_y);
	}
	g_data->p_pos_x = player_x;
	g_data->p_pos_y = player_y;
}
