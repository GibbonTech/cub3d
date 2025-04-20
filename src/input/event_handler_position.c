/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/06 14:29:07 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_basic_position(t_data *data, int map_x, int map_y)
{
	if (map_y < 0 || map_x < 0 || !data->map[map_y] || !data->map[map_y][map_x]
		|| data->map[map_y][map_x] == '1' || data->map[map_y][map_x] == ' ')
		return (0);
	return (1);
}

static int	check_padding_y_minus(t_data *data, double x, double y)
{
	int	map_x;
	int	pad_y;

	map_x = (int)x;
	pad_y = (int)(y - WALL_PADDING);
	if (pad_y >= 0 && pad_y < data->map_height && map_x >= 0
		&& map_x < (int)ft_strlen(data->map[pad_y])
		&& data->map[pad_y][map_x] == '1')
		return (0);
	return (1);
}

static int	check_padding_y_plus(t_data *data, double x, double y)
{
	int	map_x;
	int	pad_y;

	map_x = (int)x;
	pad_y = (int)(y + WALL_PADDING);
	if (pad_y >= 0 && pad_y < data->map_height && map_x >= 0
		&& map_x < (int)ft_strlen(data->map[pad_y])
		&& data->map[pad_y][map_x] == '1')
		return (0);
	return (1);
}

int	is_valid_position(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (!check_basic_position(data, map_x, map_y))
		return (0);
	if (!check_padding_y_minus(data, x, y))
		return (0);
	if (!check_padding_y_plus(data, x, y))
		return (0);
	if (!check_padding_x(data, x, y))
		return (0);
	return (1);
}
