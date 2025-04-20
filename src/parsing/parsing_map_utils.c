/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 14:42:34 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	count_map_dimensions(char **file_content, int start,
	int *width, int *height)
{
	int	i;
	int	len;

	*width = 0;
	*height = 0;
	i = start;
	while (file_content[i])
	{
		len = ft_strlen(file_content[i]);
		if (len > *width)
			*width = len;
		(*height)++;
		i++;
	}
}
