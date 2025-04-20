/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:56:35 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	prepare_wall_drawing(t_data *data, t_tex_info *tex_info, int *bounds)
{
	int	pitch_offset;

	pitch_offset = (int)(data->player.pitch * data->window_height / 2);
	prepare_texture_drawing(data, &tex_info->step, &tex_info->pos);
	tex_info->num = get_texture_number(data);
	bounds[0] = data->drawstart + pitch_offset;
	bounds[1] = data->drawend + pitch_offset;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[0] >= data->window_height)
		bounds[0] = data->window_height - 1;
	if (bounds[1] >= data->window_height)
		bounds[1] = data->window_height - 1;
	if (bounds[1] < 0)
		bounds[1] = 0;
}

void	draw_ceiling_section(t_data *data, int x, int wall_start)
{
	int	y;

	y = 0;
	while (y < wall_start)
	{
		draw_ceiling(data, x, y);
		y++;
	}
}

void	draw_wall_section(t_wall_section *section)
{
	int	y;

	y = section->start;
	while (y < section->end)
	{
		draw_wall(section->data, section->x, y, section->tex_info);
		y++;
	}
}

void	draw_floor_section(t_data *data, int x, int wall_end)
{
	int	y;

	y = wall_end;
	while (y < data->window_height)
	{
		draw_floor(data, x, y);
		y++;
	}
}
