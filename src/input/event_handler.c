/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:00:41 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

static void	check_pitch_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->player.pitch += PITCH_SPEED;
		if (data->player.pitch > MAX_PITCH)
			data->player.pitch = MAX_PITCH;
		data->is_resetting_pitch = 0;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->player.pitch -= PITCH_SPEED;
		if (data->player.pitch < -MAX_PITCH)
			data->player.pitch = -MAX_PITCH;
		data->is_resetting_pitch = 0;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		data->is_resetting_pitch = 1;
}

static void	check_movement_keys(t_data *data)
{
	check_basic_movement(data);
	check_pitch_keys(data);
	if (data->is_resetting_pitch)
	{
		data->player.pitch *= 0.9;
		if (fabs(data->player.pitch) < 0.01)
		{
			data->player.pitch = 0.0;
			data->is_resetting_pitch = 0;
		}
	}
}

static void	check_mouse_movement(t_data *data, int32_t *last_x, int32_t *last_y)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	int32_t	dx;

	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	if (*last_x == -1 || *last_y == -1)
	{
		*last_x = mouse_x;
		*last_y = mouse_y;
		return ;
	}
	dx = mouse_x - *last_x;
	if (dx != 0)
	{
		rotate_player(data, dx * 0.005);
		mlx_set_mouse_pos(data->mlx, WINDOW_W / 2, WINDOW_H / 2);
		*last_x = WINDOW_W / 2;
		*last_y = WINDOW_H / 2;
	}
}

void	check_keys(void *param)
{
	t_data		*data;
	static int	last_x = -1;
	static int	last_y = -1;

	data = (t_data *)param;
	check_movement_keys(data);
	check_mouse_movement(data, &last_x, &last_y);
}
