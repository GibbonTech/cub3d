/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:32:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/12 15:32:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static uint32_t	get_cell_color(t_data *data, int mini_x, int mini_y)
{
	if (data->map[mini_y][mini_x] == '1')
		return (0xFFFFFFAA);
	else if (mini_y == (int)data->player.posy
		&& mini_x == (int)data->player.posx)
		return (0xFF0000AA);
	else if (data->map[mini_y][mini_x] == '0')
		return (0x44444488);
	else
		return (0x00000000);
}

static void	draw_cell_pixels(t_data *data, t_cell_params *params)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < params->cell_size)
	{
		j = 0;
		while (j < params->cell_size)
		{
			px = params->x * params->cell_size + i;
			py = params->y * params->cell_size + j;
			if (px >= 0 && px < params->map_size && py >= 0
				&& py < params->map_size)
				mlx_put_pixel(data->minimap, px, py, params->color);
			j++;
		}
		i++;
	}
}

void	draw_map_cell(t_data *data, t_cell_coords *coords)
{
	t_cell_params	params;

	params.x = coords->x;
	params.y = coords->y;
	params.mini_x = coords->mini_x;
	params.mini_y = coords->mini_y;
	params.cell_size = 15;
	params.map_size = 200;
	params.color = get_cell_color(data, coords->mini_x, coords->mini_y);
	draw_cell_pixels(data, &params);
	if (coords->mini_y == (int)data->player.posy
		&& coords->mini_x == (int)data->player.posx)
		draw_player_dir_indicator(data, coords->x, coords->y, params.cell_size);
}
