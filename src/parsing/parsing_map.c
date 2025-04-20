/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 14:35:24 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_map(t_data *data, char **file_content, int i)
{
	int	width;
	int	height;
	int	start;

	start = i;
	count_map_dimensions(file_content, start, &width, &height);
	data->map = create_map(file_content, start, width, height);
	if (!data->map)
		return (1);
	data->map_height = height;
	return (validate_map(data));
}
