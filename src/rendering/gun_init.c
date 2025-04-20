/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by augment           #+#    #+#             */
/*   Updated: 2025/04/12 14:12:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static mlx_texture_t	*load_gun_texture(void)
{
	mlx_texture_t	*gun_texture;
	char			*path;

	path = "textures/gunhehe.png";
	gun_texture = mlx_load_png(path);
	if (!gun_texture)
	{
		printf("Failed to load gun texture, using simple gun instead\n");
		return (NULL);
	}
	return (gun_texture);
}

static int	create_gun_image(t_data *data, int gun_width, int gun_height)
{
	data->gun_img = mlx_new_image(data->mlx, gun_width, gun_height);
	if (!data->gun_img)
	{
		printf("Failed to create gun image\n");
		return (0);
	}
	return (1);
}

static uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t		*pixel;
	uint32_t	color;

	color = 0;
	if (tex_x >= 0 && tex_x < (int)texture->width
		&& tex_y >= 0 && tex_y < (int)texture->height)
	{
		pixel = &texture->pixels[(tex_y * texture->width + tex_x)
			* texture->bytes_per_pixel];
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | pixel[3];
	}
	return (color);
}

static void	fill_gun_image(t_data *data, mlx_texture_t *texture,
	int gun_width, int gun_height)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	y = 0;
	while (y < gun_height)
	{
		x = 0;
		while (x < gun_width)
		{
			tex_x = (x * texture->width) / gun_width;
			tex_y = (y * texture->height) / gun_height;
			color = get_texture_color(texture, tex_x, tex_y);
			if ((color & 0xFF) > 0)
				mlx_put_pixel(data->gun_img, x, y, color);
			x++;
		}
		y++;
	}
}

void	init_gun(t_data *data)
{
	mlx_texture_t	*gun_texture;
	int				gun_width;
	int				gun_height;
	int				center_x;
	int				offset_x;

	gun_texture = load_gun_texture();
	if (!gun_texture)
		return ;
	gun_width = 250;
	gun_height = 170;
	if (!create_gun_image(data, gun_width, gun_height))
	{
		mlx_delete_texture(gun_texture);
		return ;
	}
	fill_gun_image(data, gun_texture, gun_width, gun_height);
	center_x = data->window_width / 2;
	offset_x = center_x * 0.15;
	mlx_image_to_window(data->mlx, data->gun_img,
		center_x - (gun_width / 2) - offset_x,
		data->window_height - gun_height);
	mlx_delete_texture(gun_texture);
}
