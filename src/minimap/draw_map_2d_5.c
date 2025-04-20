/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calculate_direction_points(t_dir_params *params,
		int *center_x, int *center_y)
{
	*center_x = params->x * params->cell_size + params->cell_size / 2;
	*center_y = params->y * params->cell_size + params->cell_size / 2;
}

static void	calculate_line_point(t_line_data *line, t_dir_params *params, int i,
		int *coords)
{
	float	t;

	t = (float)i / params->cell_size;
	coords[0] = line->center_x + (int)((line->dir_x - line->center_x) * t);
	coords[1] = line->center_y + (int)((line->dir_y - line->center_y) * t);
}

static void	draw_direction_line(t_data *data, int center_x, int center_y,
		t_dir_params *params)
{
	t_line_data	line;
	int			i;
	int			coords[2];

	line.center_x = center_x;
	line.center_y = center_y;
	line.dir_x = center_x + (int)(data->player.dirx * params->cell_size);
	line.dir_y = center_y + (int)(data->player.diry * params->cell_size);
	i = 0;
	while (i < params->cell_size)
	{
		calculate_line_point(&line, params, i, coords);
		if (coords[0] >= 0 && coords[0] < params->map_size && coords[1] >= 0
			&& coords[1] < params->map_size)
			mlx_put_pixel(data->minimap, coords[0], coords[1], 0x00FF00AA);
		i++;
	}
}

static void	init_dir_params(t_dir_params *params, int x, int y, int cell_size)
{
	params->x = x;
	params->y = y;
	params->cell_size = cell_size;
	params->map_size = 200;
}

void	draw_player_dir_indicator(t_data *data, int x, int y, int cell_size)
{
	t_dir_params		params;
	t_indicator_data	ind_data;

	init_dir_params(&params, x, y, cell_size);
	calculate_direction_points(&params, &ind_data.center_x,
		&ind_data.center_y);
	draw_direction_line(data, ind_data.center_x, ind_data.center_y, &params);
}
