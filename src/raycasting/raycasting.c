/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:56:35 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	draw_line(t_data *data, int x)
{
	t_tex_info		tex_info;
	t_wall_section	section;
	int				bounds[2];

	prepare_wall_drawing(data, &tex_info, bounds);
	draw_ceiling_section(data, x, bounds[0]);
	section.data = data;
	section.x = x;
	section.start = bounds[0];
	section.end = bounds[1];
	section.tex_info = &tex_info;
	draw_wall_section(&section);
	draw_floor_section(data, x, bounds[1]);
}

void	render_frame(t_data *data)
{
	static int		frame_count = 0;
	static double	last_time = 0;
	static double	fps = 0;

	if (!data->img || !data->img->pixels)
	{
		printf("Error: Image not properly initialized\n");
		return ;
	}
	update_fps(data, &frame_count, &last_time, &fps);
	ft_memset(data->img->pixels, 0,
		data->window_width * data->window_height * sizeof(uint32_t));
	render_walls(data);
	draw_map_2d(data);
	draw_gun(data);
	draw_crosshair(data);
}
