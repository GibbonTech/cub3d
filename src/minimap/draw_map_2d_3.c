/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clear_minimap(t_data *data, int map_size)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_size)
	{
		x = 0;
		while (x < map_size)
		{
			mlx_put_pixel(data->minimap, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

static void	process_map_cell(t_data *data, t_cell_coords *coords)
{
	if (coords->mini_y >= 0 && coords->mini_x >= 0
		&& coords->mini_y < data->map_height
		&& data->map[coords->mini_y]
		&& coords->mini_x < (int)ft_strlen(data->map[coords->mini_y]))
	{
		draw_map_cell(data, coords);
	}
}

static void	draw_map_elements(t_data *data)
{
	t_map_elem_vars	vars;

	vars.y = 0;
	while (vars.y < 10)
	{
		vars.x = 0;
		while (vars.x < 10)
		{
			vars.coords.x = vars.x;
			vars.coords.y = vars.y;
			vars.coords.mini_y = (int)data->player.posy - 5 + vars.y;
			vars.coords.mini_x = (int)data->player.posx - 5 + vars.x;
			process_map_cell(data, &vars.coords);
			vars.x++;
		}
		vars.y++;
	}
}

void	draw_map_2d(t_data *data)
{
	int	cell_size;
	int	map_size;
	int	center_x;
	int	center_y;

	cell_size = 15;
	map_size = 200;
	clear_minimap(data, map_size);
	draw_map_elements(data);
	center_x = 5 * cell_size + cell_size / 2;
	center_y = 5 * cell_size + cell_size / 2;
	draw_fov_rays(data, center_x, center_y, map_size);
}
