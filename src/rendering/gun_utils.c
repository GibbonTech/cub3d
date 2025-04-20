/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by augment           #+#    #+#             */
/*   Updated: 2025/04/06 19:04:40 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_gun_barrel(t_data *data, t_gun_info *gun_info)
{
	int	x;
	int	y;

	y = 0;
	while (y < gun_info->height)
	{
		x = 0;
		while (x < gun_info->width)
		{
			if (y > gun_info->height / 2 && y < gun_info->height * 0.7
				&& x > gun_info->width * 0.3 && x < gun_info->width * 0.7)
				mlx_put_pixel(data->img, gun_info->start_x + x,
					gun_info->start_y + y, 0x444444FF);
			x++;
		}
		y++;
	}
}

void	draw_gun_handle(t_data *data, t_gun_info *gun_info)
{
	int	x;
	int	y;

	y = 0;
	while (y < gun_info->height)
	{
		x = 0;
		while (x < gun_info->width)
		{
			if (y > gun_info->height * 0.7
				&& x > gun_info->width * 0.4 && x < gun_info->width * 0.6)
				mlx_put_pixel(data->img, gun_info->start_x + x,
					gun_info->start_y + y, 0x222222FF);
			x++;
		}
		y++;
	}
}
