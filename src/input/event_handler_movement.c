/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:43:54 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_player(t_data *data, double dir)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = data->move_speed;
	new_x = data->player.posx + dir * data->player.dirx * move_speed;
	new_y = data->player.posy + dir * data->player.diry * move_speed;
	if (is_valid_position(data, new_x, data->player.posy))
		data->player.posx = new_x;
	if (is_valid_position(data, data->player.posx, new_y))
		data->player.posy = new_y;
}

void	strafe_player(t_data *data, double dir)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = data->move_speed;
	new_x = data->player.posx - dir * data->player.diry * move_speed;
	new_y = data->player.posy + dir * data->player.dirx * move_speed;
	if (is_valid_position(data, new_x, data->player.posy))
		data->player.posx = new_x;
	if (is_valid_position(data, data->player.posx, new_y))
		data->player.posy = new_y;
}

void	rotate_player(t_data *data, double dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED * dir;
	old_dir_x = data->player.dirx;
	old_plane_x = data->player.planex;
	data->player.dirx = data->player.dirx * cos(rot_speed) - data->player.diry
		* sin(rot_speed);
	data->player.diry = old_dir_x * sin(rot_speed) + data->player.diry
		* cos(rot_speed);
	data->player.planex = data->player.planex * cos(rot_speed)
		- data->player.planey * sin(rot_speed);
	data->player.planey = old_plane_x * sin(rot_speed) + data->player.planey
		* cos(rot_speed);
}
