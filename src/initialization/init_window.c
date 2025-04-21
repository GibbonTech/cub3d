/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:58:10 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>
#include <stdlib.h>

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WINDOW_W, WINDOW_H, "Cub3D", true);
	if (!data->mlx)
		error_msg_exit("MLX initialization failed.", data);
}

static void	init_images(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WINDOW_W, WINDOW_H);
	if (!data->img)
		error_msg_exit("Image creation failed.", data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static void	create_minimap_image(t_data *data)
{
	data->minimap = mlx_new_image(data->mlx, 200, 200);
	if (!data->minimap)
		error_msg_exit("Minimap creation failed.", data);
	data->minimap->enabled = true;
	mlx_image_to_window(data->mlx, data->minimap, 10, 10);
}

void	init_window(t_data *data)
{
	data->window_width = WINDOW_W;
	data->window_height = WINDOW_H;
	init_mlx(data);
	init_images(data);
	create_minimap_image(data);
	data->gun_img = NULL;
	data->floor_img = NULL;
}
