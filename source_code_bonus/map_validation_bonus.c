/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:51:25 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 22:08:13 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(char **map, char *map_file)
{
	t_map_data	m_data;

	map_data_init(&m_data);
	if (map)
	{
		if (valid_count(map, &m_data) && valid_walls(map, &m_data) \
			&& valid_characters(map) && valid_extension(map_file))
		{
			return (1);
		}
	}
	return (0);
}

int	valid_count(char **map, t_map_data *data)
{
	int	height_count;
	int	width_count;

	height_count = 0;
	while (map[height_count])
	{
		width_count = 0;
		while (map[height_count][width_count])
		{
			if (map[height_count][width_count] == 'E')
				data->goal_count++;
			if (map[height_count][width_count] == 'P')
				data->player_count++;
			if (map[height_count][width_count] == 'C')
				data->collectable_count++;
			width_count++;
		}
		height_count++;
	}
	if (data->goal_count != 1 || data->player_count != 1 \
			|| data->collectable_count == 0)
	{
		return (0);
	}
	return (1);
}

int	valid_walls(char **map, t_map_data *data)
{
	int	height_count;
	int	width_count;

	data->collum = ft_strlen(map[0]);
	data->line = 0;
	while (map[data->line])
		data->line++;
	height_count = 0;
	while (map[height_count])
	{
		width_count = 0;
		while (map[height_count][width_count])
		{
			if (map[0][width_count] != '1' || map[data->line - 1] \
					[width_count] != '1' || map[height_count][0] != '1' \
					|| map[height_count][data->collum - 1] != '1')
				return (0);
			width_count++;
		}
		if (width_count != data->collum)
			return (0);
		height_count++;
	}
	return (1);
}

int	valid_characters(char **map)
{
	int	height_count;
	int	width_count;

	height_count = 0;
	while (map[height_count])
	{
		width_count = 0;
		while (map[height_count][width_count])
		{
			if (map[height_count][width_count] != '0' && map[height_count] \
					[width_count] != '1' && map[height_count][width_count] \
					!= 'C' && map[height_count][width_count] != 'E' && \
					map[height_count][width_count] != 'P')
			{
				return (0);
			}
			width_count++;
		}
		height_count++;
	}
	return (1);
}

int	valid_extension(char *map_file)
{
	char	*extension;

	if (!map_file)
	{
		return (0);
	}
	extension = ft_strrchr(map_file, '.');
	if (ft_strncmp(extension, ".ber", 5))
	{
		return (0);
	}
	return (1);
}
