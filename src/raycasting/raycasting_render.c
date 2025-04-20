/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:56:35 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_fps(t_data *data, int *frame_count, double *last_time,
	double *fps)
{
	double	current_time;
	char	title[64];

	(*frame_count)++;
	current_time = mlx_get_time();
	if (*frame_count % 10 == 0 && *last_time > 0)
	{
		*fps = 10.0 / (current_time - *last_time);
		snprintf(title, sizeof(title), "cub3D - %.1f FPS", *fps);
		mlx_set_window_title(data->mlx, title);
		if (*frame_count <= 30)
			printf("FPS: %.1f\\n", *fps);
	}
	*last_time = current_time;
}

void	render_walls(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->window_width)
	{
		get_step_for_check(data, x);
		calc_side_dist(data);
		ft_dda(data);
		ft_lineheight(data);
		draw_line(data, x);
		x++;
	}
}
