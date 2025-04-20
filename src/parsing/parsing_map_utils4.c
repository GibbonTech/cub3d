/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 15:49:38 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	prepare_map_creation(t_map_info *info, int start, int width)
{
	info->start = start;
	info->width = width;
}

static void	check_map_allocation(char **map)
{
	if (!map[0])
	{
		free_map(map);
		return ;
	}
}

char	**create_map(char **file_content, int start, int width, int height)
{
	char			**map;
	t_map_params	params;
	t_map_info		info;

	prepare_map_creation(&info, start, width);
	map = allocate_map_memory(height);
	if (!map)
		return (NULL);
	init_map_params(&params, file_content, map, &info);
	allocate_map_rows(map, width, height);
	check_map_allocation(map);
	if (!map[0])
		return (NULL);
	fill_map_content(&params, height);
	map[height] = NULL;
	return (map);
}
