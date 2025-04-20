/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 15:28:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill_map_line(t_map_params *params)
{
	int	j;

	j = 0;
	while (params->file_content[params->start + params->i][j]
		&& j < params->width)
	{
		if (params->file_content[params->start + params->i][j] == ' '
			|| params->file_content[params->start + params->i][j] == '\n')
			params->map[params->i][j] = ' ';
		else
			params->map[params->i][j] = params->file_content[params->start
				+ params->i][j];
		j++;
	}
	while (j < params->width)
		params->map[params->i][j++] = ' ';
	params->map[params->i][j] = '\0';
}

void	init_map_params(t_map_params *params, char **file_content, char **map,
		t_map_info *info)
{
	params->file_content = file_content;
	params->start = info->start;
	params->width = info->width;
	params->map = map;
}

char	**allocate_map_memory(int height)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	return (map);
}

void	allocate_map_rows(char **map, int width, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		i++;
	}
}

void	fill_map_content(t_map_params *params, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		params->i = i;
		fill_map_line(params);
		i++;
	}
}
