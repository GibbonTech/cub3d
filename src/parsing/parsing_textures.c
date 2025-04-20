/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:58:54 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	try_load_texture_without_prefix(t_data *data, int i)
{
	printf("Trying without ./ prefix: %s\n", data->texture_paths[i] + 2);
	data->textures[i] = mlx_load_png(data->texture_paths[i] + 2);
	if (!data->textures[i])
	{
		printf("Error: Failed to load texture without prefix\n");
		return (1);
	}
	printf("Loaded texture without prefix\n");
	return (0);
}

static int	load_wall_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("Loading wall texture from: %s\n", data->texture_paths[i]);
		data->textures[i] = mlx_load_png(data->texture_paths[i]);
		if (!data->textures[i])
		{
			printf("Error: Failed to load texture\n");
			if (data->texture_paths[i][0] == '.'
				&& data->texture_paths[i][1] == '/')
			{
				if (try_load_texture_without_prefix(data, i) != 0)
					return (1);
			}
			else
				return (1);
		}
		else
			printf("Successfully loaded texture\n");
		i++;
	}
	return (0);
}

static int	load_floor_texture(t_data *data)
{
	char	*path;

	path = "textures/floor.png";
	printf("Loading floor texture from: %s\n", path);
	data->floor_texture = mlx_load_png(path);
	if (!data->floor_texture)
	{
		printf("Error: Failed to load floor texture\n");
		return (1);
	}
	printf("Floor texture loaded successfully. Width: %d, Height: %d\n",
		data->floor_texture->width, data->floor_texture->height);
	return (0);
}

int	set_textures(t_data *data)
{
	data->textures = malloc(sizeof(mlx_texture_t *) * 4);
	if (!data->textures)
		return (1);
	ft_memset(data->textures, 0, sizeof(mlx_texture_t *) * 4);
	if (load_wall_textures(data) != 0)
	{
		free_wall_textures(data);
		return (1);
	}
	if (load_floor_texture(data) != 0)
	{
		free_wall_textures(data);
		return (1);
	}
	return (0);
}
