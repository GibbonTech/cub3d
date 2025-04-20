/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 14:56:41 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_invalid_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' &&
				data->map[i][j] != 'N' && data->map[i][j] != 'S' &&
				data->map[i][j] != 'E' && data->map[i][j] != 'W' &&
				data->map[i][j] != ' ')
			{
				printf("Error: Invalid character '%c' in map at [%d,%d]\n",
					data->map[i][j], i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	process_player_position(t_data *data, int i, int j,
	int *player_count)
{
	(*player_count)++;
	data->orientation = data->map[i][j];
	data->yposition = i;
	data->xposition = j;
	data->map[i][j] = '0';
}

static int	check_player_position(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
				process_player_position(data, i, j, &player_count);
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Error: Map must have exactly one player position (found %d)\n",
			player_count);
		return (1);
	}
	return (0);
}

static int	check_map_walls(t_data *data)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(data->map);
	if (!map_copy)
		return (1);
	result = check_map_closure(map_copy, data->xposition, data->yposition);
	free_map(map_copy);
	if (result)
	{
		printf("Error: Map is not properly enclosed by walls\n");
		return (1);
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (check_invalid_chars(data))
		return (1);
	if (check_player_position(data))
		return (1);
	if (check_map_walls(data))
		return (1);
	set_player_direction(data);
	return (0);
}
