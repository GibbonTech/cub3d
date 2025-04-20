/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by augment           #+#    #+#             */
/*   Updated: 2025/04/12 14:03:27 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_simple_gun_info(t_data *data, t_gun_info *gun_info)
{
	int	center_x;
	int	offset_x;

	gun_info->width = 80;
	gun_info->height = 80;
	center_x = data->window_width / 2;
	offset_x = center_x * 0.15;
	gun_info->start_x = center_x - (gun_info->width / 2) - offset_x;
	gun_info->start_y = data->window_height - gun_info->height - 20;
}

void	draw_gun(t_data *data)
{
	t_gun_info	gun_info;

	if (data->gun_img)
		return ;
	init_simple_gun_info(data, &gun_info);
	draw_gun_barrel(data, &gun_info);
	draw_gun_handle(data, &gun_info);
}

static void	draw_horizontal_line(t_data *data, int center_x,
	int center_y, int size)
{
	int	i;

	i = -size;
	while (i <= size)
	{
		mlx_put_pixel(data->img, center_x + i, center_y, 0xFFFFFFFF);
		i++;
	}
}

static void	draw_vertical_line(t_data *data, int center_x,
	int center_y, int size)
{
	int	i;

	i = -size;
	while (i <= size)
	{
		mlx_put_pixel(data->img, center_x, center_y + i, 0xFFFFFFFF);
		i++;
	}
}

void	draw_crosshair(t_data *data)
{
	int	center_x;
	int	center_y;
	int	size;

	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
	size = 5;
	draw_horizontal_line(data, center_x, center_y, size);
	draw_vertical_line(data, center_x, center_y, size);
}
