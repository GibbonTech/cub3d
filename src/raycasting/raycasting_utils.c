/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:23:56 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_side_dist(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->player.posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->player.posx)
			* data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->player.posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->player.posy)
			* data->deltadisty;
	}
}

void	ft_dda(t_data *data)
{
	while (data->hit == false)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = false;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = true;
		}
		if (data->mapx < 0 || data->mapy < 0 || data->mapy >= data->map_height
			|| !data->map[data->mapy] || data->mapx
			>= (int)ft_strlen(data->map[data->mapy])
			|| data->map[data->mapy][data->mapx] == '1'
			|| data->map[data->mapy][data->mapx] == ' ')
		{
			data->hit = true;
		}
	}
}

static void	calc_perp_wall_dist(t_data *data)
{
	if (data->side == false)
		data->perpwalldist = (data->sidedistx - data->deltadistx);
	else
		data->perpwalldist = (data->sidedisty - data->deltadisty);
	data->lineheight = (int)(data->window_height / data->perpwalldist);
}

static void	calc_wall_bounds(t_data *data)
{
	data->drawstart = -data->lineheight / 2 + data->window_height / 2;
	data->drawend = data->lineheight / 2 + data->window_height / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	else if (data->drawstart >= data->window_height)
		data->drawstart = data->window_height - 1;
	if (data->drawend >= data->window_height)
		data->drawend = data->window_height - 1;
	else if (data->drawend < 0)
		data->drawend = 0;
}

void	ft_lineheight(t_data *data)
{
	calc_perp_wall_dist(data);
	calc_wall_bounds(data);
}
