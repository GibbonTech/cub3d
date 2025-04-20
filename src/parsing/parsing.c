/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 13:51:16 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_file_error(char *file, int line_count)
{
	if (check_file_extension(file))
	{
		printf("Error: Invalid file extension. Expected .cub\n");
		return (1);
	}
	if (line_count <= 0)
	{
		printf("Error: Failed to read file or empty file\n");
		return (1);
	}
	return (0);
}

static int	handle_parsing_error(t_data *data, char **file_content,
		int error_type)
{
	if (error_type == 1)
		printf("Error: Invalid identifiers in file\n");
	else if (error_type == 2)
		printf("Error: Invalid map\n");
	else if (error_type == 3)
		printf("Error: Failed to load textures\n");
	if (file_content)
		free_map(file_content);
	if (data && data->texture_paths)
		free_texture_paths(data);
	return (1);
}

int	parse_file(t_data *data, char *file)
{
	int		line_count;
	int		i;
	char	**file_content;

	line_count = count_lines(file);
	if (check_file_error(file, line_count))
		return (1);
	file_content = read_file(file, line_count);
	if (!file_content)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (process_identifiers(data, file_content, &i) != 0)
		return (handle_parsing_error(data, file_content, 1));
	if (parse_map(data, file_content, i) != 0)
		return (handle_parsing_error(data, file_content, 2));
	free_map(file_content);
	if (set_textures(data) != 0)
		return (handle_parsing_error(data, NULL, 3));
	return (0);
}
