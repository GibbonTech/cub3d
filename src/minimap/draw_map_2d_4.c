/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:32:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_fov_rays(t_data *data, int center_x, int center_y, int map_size)
{
	double			half_fov;
	double			ray_angle_step;
	double			angle;
	t_ray_params	params;

	half_fov = FOV_ANGLE / 2.0;
	ray_angle_step = FOV_ANGLE / 30;
	angle = -half_fov;
	params.map_size = map_size;
	while (angle <= half_fov)
	{
		params.ray_angle = angle;
		params.center_x = center_x;
		params.center_y = center_y;
		draw_fov_ray(data, center_x, center_y, &params);
		angle += ray_angle_step;
	}
}
