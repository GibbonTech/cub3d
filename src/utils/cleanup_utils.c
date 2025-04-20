/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:59:57 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_wall_textures(t_data *data)
{
	int	i;

	if (!data->textures)
		return ;
	i = 0;
	while (i < 4 && data->textures[i])
	{
		mlx_delete_texture(data->textures[i]);
		i++;
	}
	free(data->textures);
	data->textures = NULL;
}

static void	free_floor_texture(t_data *data)
{
	if (data->floor_texture)
	{
		mlx_delete_texture(data->floor_texture);
		data->floor_texture = NULL;
	}
}

static void	free_game_images(t_data *data)
{
	if (data->mlx)
	{
		if (data->gun_img)
		{
			mlx_delete_image(data->mlx, data->gun_img);
			data->gun_img = NULL;
		}
		if (data->floor_img)
		{
			mlx_delete_image(data->mlx, data->floor_img);
			data->floor_img = NULL;
		}
		if (data->img)
		{
			mlx_delete_image(data->mlx, data->img);
			data->img = NULL;
		}
		if (data->minimap)
		{
			mlx_delete_image(data->mlx, data->minimap);
			data->minimap = NULL;
		}
	}
}

void	free_other_textures(t_data *data)
{
	free_floor_texture(data);
	free_game_images(data);
}

void	free_texture_paths(t_data *data)
{
	int	i;

	if (!data->texture_paths)
		return ;
	i = 0;
	while (i < 4 && data->texture_paths[i])
	{
		free(data->texture_paths[i]);
		i++;
	}
	free(data->texture_paths);
	data->texture_paths = NULL;
}
