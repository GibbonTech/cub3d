/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 13:57:08 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_step_for_check(t_data *data, int x)
{
	data->camerax = 2 * x / (double)data->window_width - 1;
	data->raydirx = data->player.dirx + data->player.planex * data->camerax;
	data->raydiry = data->player.diry + data->player.planey * data->camerax;
	data->mapx = (int)data->player.posx;
	data->mapy = (int)data->player.posy;
	if (data->raydirx == 0)
		data->deltadistx = 1e30;
	else
		data->deltadistx = fabs(1 / data->raydirx);
	if (data->raydiry == 0)
		data->deltadisty = 1e30;
	else
		data->deltadisty = fabs(1 / data->raydiry);
	data->hit = false;
}

int	get_texture_number(t_data *data)
{
	int	tex_num;

	tex_num = 0;
	if (data->side == false)
	{
		if (data->stepx < 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (data->stepy < 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	return (tex_num);
}

static void	calculate_wall_x(t_data *data)
{
	if (data->side == false)
		data->wallx = data->player.posy + data->perpwalldist * data->raydiry;
	else
		data->wallx = data->player.posx + data->perpwalldist * data->raydirx;
	data->wallx -= floor(data->wallx);
}

static void	calculate_texture_x(t_data *data, int tex_num)
{
	data->texx = (int)(data->wallx * (double)data->textures[tex_num]->width);
	if (data->side == false && data->raydirx > 0)
		data->texx = data->textures[tex_num]->width - data->texx - 1;
	if (data->side == true && data->raydiry < 0)
		data->texx = data->textures[tex_num]->width - data->texx - 1;
}

void	prepare_texture_drawing(t_data *data, double *step, double *tex_pos)
{
	int	tex_num;

	tex_num = get_texture_number(data);
	calculate_wall_x(data);
	calculate_texture_x(data, tex_num);
	*step = 1.0 * data->textures[tex_num]->height / data->lineheight;
	*tex_pos = (data->drawstart - data->window_height / 2
			+ data->lineheight / 2) * (*step);
}
