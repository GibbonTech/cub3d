/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 14:43:49 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_map_closure(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	map[y][x] = 'X';
	if (check_map_closure(map, x + 1, y) || check_map_closure(map, x - 1, y)
		|| check_map_closure(map, x, y + 1) || check_map_closure(map, x, y - 1))
		return (1);
	return (0);
}

char	**copy_map(char **map)
{
	int		i;
	char	**map_copy;

	i = 0;
	while (map[i])
		i++;
	map_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	set_north_south_direction(t_data *data)
{
	if (data->orientation == 'N')
	{
		data->player.dirx = 0.0;
		data->player.diry = -1.0;
		data->player.planex = 0.66;
		data->player.planey = 0.0;
	}
	else if (data->orientation == 'S')
	{
		data->player.dirx = 0.0;
		data->player.diry = 1.0;
		data->player.planex = -0.66;
		data->player.planey = 0.0;
	}
}

static void	set_east_west_direction(t_data *data)
{
	if (data->orientation == 'E')
	{
		data->player.dirx = 1.0;
		data->player.diry = 0.0;
		data->player.planex = 0.0;
		data->player.planey = 0.66;
	}
	else if (data->orientation == 'W')
	{
		data->player.dirx = -1.0;
		data->player.diry = 0.0;
		data->player.planex = 0.0;
		data->player.planey = -0.66;
	}
}

void	set_player_direction(t_data *data)
{
	set_north_south_direction(data);
	set_east_west_direction(data);
	data->player.posx = (double)data->xposition + 0.5;
	data->player.posy = (double)data->yposition + 0.5;
}
