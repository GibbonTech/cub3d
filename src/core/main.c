/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/12 16:08:46 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	setup_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, (void (*)(void *))render_frame, data);
	mlx_loop_hook(data->mlx, check_keys, data);
	mlx_key_hook(data->mlx, handle_key_press, data);
	mlx_mouse_hook(data->mlx, (void *)mouse_button_handler, data);
	mlx_close_hook(data->mlx, (void *)clean_exit, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

static int	check_args(int argc)
{
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments.\n");
		printf("Usage: ./cub3D <map_file.cub>\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc))
		return (1);
	init_data(&data);
	if (parse_file(&data, argv[1]) != 0)
	{
		clean_exit(&data, 1);
		return (1);
	}
	init_window(&data);
	init_gun(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	clean_exit(&data, 0);
	return (0);
}
