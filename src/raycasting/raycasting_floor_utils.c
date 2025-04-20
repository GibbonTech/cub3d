/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_floor_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:27:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_ray_directions(t_data *data, float *ray_dir)
{
	ray_dir[0] = data->player.dirx - data->player.planex;
	ray_dir[1] = data->player.diry - data->player.planey;
	ray_dir[2] = data->player.dirx + data->player.planex;
	ray_dir[3] = data->player.diry + data->player.planey;
}

void	calc_floor_steps(t_data *data, float *ray_dir, float row_dist,
		float *floor_step)
{
	float	delta_x;
	float	delta_y;

	delta_x = ray_dir[2] - ray_dir[0];
	delta_y = ray_dir[3] - ray_dir[1];
	floor_step[0] = row_dist * delta_x / data->window_width;
	floor_step[1] = row_dist * delta_y / data->window_width;
}

void	get_floor_texture_coords(t_data *data, float *pos, int *tex_coords)
{
	int		tx;
	int		ty;
	float	frac_x;
	float	frac_y;

	frac_x = pos[0] - floor(pos[0]);
	frac_y = pos[1] - floor(pos[1]);
	tx = (int)(data->floor_texture->width * frac_x);
	ty = (int)(data->floor_texture->height * frac_y);
	tx &= (data->floor_texture->width - 1);
	ty &= (data->floor_texture->height - 1);
	tex_coords[0] = tx;
	tex_coords[1] = ty;
}
