/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:56:35 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling(t_data *data, int x, int y)
{
	mlx_put_pixel(data->img, x, y, data->sky);
}

void	draw_floor(t_data *data, int x, int y)
{
	uint32_t	color;

	color = get_floor_color(data, x, y);
	mlx_put_pixel(data->img, x, y, color);
}

double	calc_wall_position(t_data *data, int y, int pitch_offset)
{
	int		adjusted_y;
	double	wall_pos;
	int		line_height_half;
	int		window_height_half;

	adjusted_y = y - pitch_offset;
	line_height_half = -data->lineheight / 2;
	window_height_half = data->window_height / 2;
	wall_pos = (double)(adjusted_y - (line_height_half + window_height_half))
		/ data->lineheight;
	if (wall_pos < 0)
		wall_pos = 0;
	if (wall_pos > 1)
		wall_pos = 1;
	return (wall_pos);
}

void	draw_wall(t_data *data, int x, int y, t_tex_info *tex_info)
{
	t_wall_vars	vars;

	vars.pitch_offset = (int)(data->player.pitch * data->window_height / 2);
	vars.wall_pos = calc_wall_position(data, y, vars.pitch_offset);
	vars.tex_y = (int)(vars.wall_pos * data->textures[tex_info->num]->height);
	vars.tex_y %= data->textures[tex_info->num]->height;
	vars.color = get_texture_pixel(data->textures[tex_info->num],
			data->texx, vars.tex_y);
	mlx_put_pixel(data->img, x, y, vars.color);
}
