/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:31 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <limits.h>

void	init_minimap_params(t_minimap *mm, t_data *data)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (data->map[i])
	{
		height++;
		i++;
	}
	mm->map_height = height;
	mm->map_width = 0;
	mm->min_x = INT_MAX;
	mm->player_x = 0;
	mm->player_y = 0;
}

static void	find_min_x_and_width(t_minimap *mm, t_data *data)
{
	int	y;
	int	x;
	int	current_width;

	y = 0;
	while (y < mm->map_height)
	{
		current_width = ft_strlen(data->map[y]);
		if (current_width > mm->map_width)
			mm->map_width = current_width;
		x = 0;
		while (x < current_width)
		{
			if (data->map[y][x] != ' ' && x < mm->min_x)
			{
				mm->min_x = x;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	init_minimap(t_minimap *mm, t_data *data)
{
	init_minimap_params(mm, data);
	find_min_x_and_width(mm, data);
	mm->player_x = MAP_OFFSET + (int)((data->player.posx - mm->min_x)
			* TILE_SIZE);
	mm->player_y = MAP_OFFSET + (int)(data->player.posy * TILE_SIZE);
}
