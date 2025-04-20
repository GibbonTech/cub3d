/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_position_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/06 14:29:07 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_padding_x_minus(t_data *data, double x, double y)
{
	int	map_y;
	int	pad_x;

	map_y = (int)y;
	pad_x = (int)(x - WALL_PADDING);
	if (map_y >= 0 && map_y < data->map_height && pad_x >= 0
		&& pad_x < (int)ft_strlen(data->map[map_y])
		&& data->map[map_y][pad_x] == '1')
		return (0);
	return (1);
}

static int	check_padding_x_plus(t_data *data, double x, double y)
{
	int	map_y;
	int	pad_x;

	map_y = (int)y;
	pad_x = (int)(x + WALL_PADDING);
	if (map_y >= 0 && map_y < data->map_height && pad_x >= 0
		&& pad_x < (int)ft_strlen(data->map[map_y])
		&& data->map[map_y][pad_x] == '1')
		return (0);
	return (1);
}

int	check_padding_x(t_data *data, double x, double y)
{
	if (!check_padding_x_minus(data, x, y))
		return (0);
	if (!check_padding_x_plus(data, x, y))
		return (0);
	return (1);
}
