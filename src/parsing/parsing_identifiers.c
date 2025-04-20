/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 13:46:42 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	process_texture_identifier(t_data *data, char **line_split)
{
	char	*tmp;
	int		len;

	if (!line_split || !line_split[0] || !line_split[1])
		return (1);
	tmp = line_split[1];
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	if (ft_strncmp(line_split[0], "NO", 3) == 0 && !data->texture_paths[0])
		data->texture_paths[0] = ft_strdup(tmp);
	else if (ft_strncmp(line_split[0], "SO", 3) == 0 && !data->texture_paths[1])
		data->texture_paths[1] = ft_strdup(tmp);
	else if (ft_strncmp(line_split[0], "WE", 3) == 0 && !data->texture_paths[2])
		data->texture_paths[2] = ft_strdup(tmp);
	else if (ft_strncmp(line_split[0], "EA", 3) == 0 && !data->texture_paths[3])
		data->texture_paths[3] = ft_strdup(tmp);
	else
		return (1);
	return (0);
}

static int	parse_color(char *str)
{
	char	**split;
	int		rgb[3];
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (-1);
	i = 0;
	while (split[i] && i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_map(split);
			return (-1);
		}
		i++;
	}
	free_map(split);
	if (i != 3)
		return (-1);
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 255);
}

int	process_color_identifier(t_data *data, char **line_split)
{
	char	*tmp;
	int		len;

	if (!line_split || !line_split[0] || !line_split[1])
		return (1);
	tmp = line_split[1];
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	if (ft_strncmp(line_split[0], "F", 2) == 0)
	{
		data->floor = parse_color(tmp);
		if (data->floor == (uint32_t) - 1)
			return (1);
	}
	else if (ft_strncmp(line_split[0], "C", 2) == 0)
	{
		data->sky = parse_color(tmp);
		if (data->sky == (uint32_t) - 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	process_identifiers(t_data *data, char **file_content, int *i)
{
	if (init_texture_paths(data) != 0)
		return (1);
	*i = 0;
	while (file_content[*i])
	{
		if (ft_strlen(file_content[*i]) <= 1)
		{
			(*i) += 1;
			continue ;
		}
		if (process_line(data, file_content, i) != 0)
			return (1);
		if (data->texture_paths[0] && data->texture_paths[1]
			&& data->texture_paths[2] && data->texture_paths[3]
			&& data->floor != 0 && data->sky != 0)
			break ;
		(*i) += 1;
	}
	if (check_all_identifiers(data) != 0)
		return (1);
	(*i) += 1;
	return (0);
}
