/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 14:24:30 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	mouse_button_handler(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	(void)mods;
	(void)param;
	if (action == MLX_PRESS)
	{
		if (button == MLX_MOUSE_BUTTON_LEFT)
			printf("Left mouse button pressed\n");
		else if (button == MLX_MOUSE_BUTTON_RIGHT)
			printf("Right mouse button pressed\n");
	}
}

void	debug_mouse_position(void *param)
{
	t_data	*data;
	int32_t	mouse_x;
	int32_t	mouse_y;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	printf("Current mouse position: %d, %d\n", mouse_x, mouse_y);
}

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	dx;
	double	sens;

	data = (t_data *)param;
	sens = 0.05;
	dx = xpos - (WINDOW_W / 2);
	if (dx != 0)
		rotate_player(data, dx * sens);
	(void)ypos;
}
