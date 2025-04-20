/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:31 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <limits.h>

int	get_tile_color(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (COLOR_WALL_MINI);
	if (data->map[y][x] == '0' || data->map[y][x] == 'N' ||
		data->map[y][x] == 'S' || data->map[y][x] == 'W' ||
		data->map[y][x] == 'E')
		return (COLOR_FLOOR_MINI);
	return (0x000000FF);
}

static void	draw_tile_pixels(t_data *data, int pixel_x, int pixel_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(data->minimap, pixel_x + i, pixel_y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_single_tile(t_data *data, t_minimap *mm, int x, int y)
{
	int	pixel_x;
	int	pixel_y;
	int	color;

	pixel_x = MAP_OFFSET + (x - mm->min_x) * TILE_SIZE;
	pixel_y = MAP_OFFSET + y * TILE_SIZE;
	color = get_tile_color(data, x, y);
	if (data->map[y][x] != ' ')
		draw_tile_pixels(data, pixel_x, pixel_y, color);
}

void	draw_map_grid(t_data *data, t_minimap *mm)
{
	int	x;
	int	y;
	int	current_width;

	y = 0;
	while (y < mm->map_height)
	{
		current_width = ft_strlen(data->map[y]);
		x = mm->min_x;
		while (x < current_width)
		{
			draw_single_tile(data, mm, x, y);
			x++;
		}
		y++;
	}
}
