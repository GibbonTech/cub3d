/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:35 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:36 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_data *data, t_minimap *mm)
{
	int	i;
	int	j;

	i = -PLAYER_SIZE;
	while (i <= PLAYER_SIZE)
	{
		j = -PLAYER_SIZE;
		while (j <= PLAYER_SIZE)
		{
			mlx_put_pixel(data->minimap,
				mm->player_x + i,
				mm->player_y + j,
				COLOR_PLAYER_MINI);
			j++;
		}
		i++;
	}
}

static void	draw_direction_line(t_data *data, t_minimap *mm, int dir_x,
	int dir_y)
{
	int		i;
	int		x;
	int		y;
	float	t;

	i = 0;
	while (i < TILE_SIZE * 2)
	{
		t = (float)i / (TILE_SIZE * 2);
		x = mm->player_x + (int)((dir_x - mm->player_x) * t);
		y = mm->player_y + (int)((dir_y - mm->player_y) * t);
		if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
			mlx_put_pixel(data->minimap, x, y, COLOR_VISION_MINI);
		i++;
	}
}

void	draw_player_direction(t_data *data, t_minimap *mm)
{
	int	dir_x;
	int	dir_y;

	dir_x = mm->player_x + (int)(data->player.dirx * TILE_SIZE * 2);
	dir_y = mm->player_y + (int)(data->player.diry * TILE_SIZE * 2);
	draw_direction_line(data, mm, dir_x, dir_y);
}
