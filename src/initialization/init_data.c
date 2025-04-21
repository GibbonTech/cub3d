/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 16:00:13 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_msg_exit(char *msg, t_data *data)
{
	if (msg)
		printf("Error: %s\n", msg);
	clean_exit(data, 1);
}

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->textures = NULL;
	data->texture_paths = NULL;
	data->map_txt = NULL;
	data->map = NULL;
	data->floor_texture = NULL;
	data->move_speed = 0.05;
	data->player.pitch = 0.0;
	data->is_resetting_pitch = 0;
}
