/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:27:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calc_floor_coords(t_data *data, int x, float *ray_dir,
		float *floor_pos)
{
	float	row_dist;
	float	floor_step[2];
	float	pos_z;
	int		horizon;
	int		p;

	horizon = data->window_height / 2;
	p = floor_pos[2] - horizon;
	if (p == 0)
		p = 1;
	pos_z = 0.5 * data->window_height;
	row_dist = pos_z / p;
	calc_floor_steps(data, ray_dir, row_dist, floor_step);
	floor_pos[0] = data->player.posx + row_dist * ray_dir[0];
	floor_pos[0] += floor_step[0] * x;
	floor_pos[1] = data->player.posy + row_dist * ray_dir[1];
	floor_pos[1] += floor_step[1] * x;
}

static void	calculate_floor_position(t_data *data, int x, int y, float *pos)
{
	float	ray_dir[4];
	float	floor_pos[3];

	calc_ray_directions(data, ray_dir);
	floor_pos[2] = y;
	calc_floor_coords(data, x, ray_dir, floor_pos);
	pos[0] = floor_pos[0];
	pos[1] = floor_pos[1];
}

static int	should_use_texture(t_data *data, int y, int *adjusted_y)
{
	int	horizon;

	if (!data->floor_texture)
		return (0);
	horizon = data->window_height / 2;
	*adjusted_y = y - (int)(data->player.pitch * data->window_height / 2);
	if (*adjusted_y < horizon)
		return (0);
	return (1);
}

uint32_t	get_floor_color(t_data *data, int x, int y)
{
	float	pos[2];
	int		tex_coords[2];
	int		adjusted_y;

	if (!should_use_texture(data, y, &adjusted_y))
		return (data->floor);
	calculate_floor_position(data, x, adjusted_y, pos);
	get_floor_texture_coords(data, pos, tex_coords);
	return (get_texture_pixel(data->floor_texture, tex_coords[0],
			tex_coords[1]));
}
