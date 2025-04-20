/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 13:46:42 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_texture_paths(t_data *data)
{
	data->texture_paths = (char **)malloc(sizeof(char *) * 5);
	if (!data->texture_paths)
		return (1);
	ft_memset(data->texture_paths, 0, sizeof(char *) * 5);
	return (0);
}

int	process_line(t_data *data, char **file_content, int *i)
{
	char	**line_split;
	int		ret;

	if (ft_strlen(file_content[*i]) <= 1)
		return (0);
	line_split = ft_split(file_content[*i], ' ');
	if (!line_split)
		return (1);
	ret = process_texture_identifier(data, line_split);
	if (ret != 0)
		ret = process_color_identifier(data, line_split);
	free_map(line_split);
	return (ret);
}

int	check_all_identifiers(t_data *data)
{
	if (!data->texture_paths[0] || !data->texture_paths[1]
		|| !data->texture_paths[2] || !data->texture_paths[3]
		|| !data->floor || !data->sky)
		return (1);
	return (0);
}
