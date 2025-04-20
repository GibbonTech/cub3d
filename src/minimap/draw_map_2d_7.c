/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:32:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/12 15:32:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calculate_ray_direction(t_data *data, double ray_angle,
		t_ray_data *ray_data)
{
	ray_data->ray_dir_x = data->player.dirx * cos(ray_angle) - data->player.diry
		* sin(ray_angle);
	ray_data->ray_dir_y = data->player.dirx * sin(ray_angle) + data->player.diry
		* cos(ray_angle);
}

static void	draw_ray_segment(t_data *data, t_segment_data *segment,
		t_ray_segment_params *params)
{
	int	w;
	int	px;
	int	py;

	w = -params->width;
	while (w <= params->width)
	{
		px = segment->cx + (int)(cos(segment->ray_angle + M_PI / 2) * w);
		py = segment->cy + (int)(sin(segment->ray_angle + M_PI / 2) * w);
		if (px >= 0 && px < params->map_size && py >= 0
			&& py < params->map_size)
			mlx_put_pixel(data->minimap, px, py, 0x00FF00FF);
		w++;
	}
}

static void	init_ray_data(t_ray_data *ray_data)
{
	ray_data->ray_length = 15 * 2;
	ray_data->r = 0;
}

static void	calculate_ray_angle(int center_x, int center_y,
		t_ray_data *ray_data, double *ray_angle)
{
	ray_data->dx = (center_x + (int)(ray_data->ray_dir_x
				* ray_data->ray_length)) - center_x;
	ray_data->dy = (center_y + (int)(ray_data->ray_dir_y
				* ray_data->ray_length)) - center_y;
	*ray_angle = atan2(ray_data->dy, ray_data->dx);
}

void	draw_fov_ray(t_data *data, int center_x, int center_y,
		t_ray_params *params)
{
	t_ray_data				ray_data;
	double					ray_angle;
	t_ray_segment_params	segment_params;
	t_segment_data			segment;

	ray_angle = params->ray_angle;
	calculate_ray_direction(data, ray_angle, &ray_data);
	init_ray_data(&ray_data);
	calculate_ray_angle(center_x, center_y, &ray_data, &ray_angle);
	segment_params.map_size = params->map_size;
	while (ray_data.r < ray_data.ray_length)
	{
		segment_params.width = 1 + ray_data.r / 5;
		ray_data.cx = center_x + (int)(cos(ray_angle) * ray_data.r);
		ray_data.cy = center_y + (int)(sin(ray_angle) * ray_data.r);
		segment.cx = ray_data.cx;
		segment.cy = ray_data.cy;
		segment.ray_angle = ray_angle;
		draw_ray_segment(data, &segment, &segment_params);
		ray_data.r++;
	}
}
