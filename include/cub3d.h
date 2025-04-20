/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:15:00 by rick              #+#    #+#             */
/*   Updated: 2025/04/13 15:57:54 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_W 1280
# define WINDOW_H 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_CELL_SIZE 10
# define TILE_SIZE 10
# define MAP_OFFSET 10
# define MAP_SIZE 200
# define PLAYER_SIZE 5
# define FOV_ANGLE 1.1519173063162575 // 66 degrees in radians

# define COLOR_PLAYER_MINI 0xFF0000FF
# define COLOR_VISION_MINI 0x00FF00FF
# define COLOR_WALL_MINI 0xFFFFFFFF
# define COLOR_FLOOR_MINI 0x444444FF
# define M_PI_2 1.5707963267948966
# define ROT_SPEED 0.03
# define WALL_PADDING 0.2
# define PITCH_SPEED 0.05
# define MAX_PITCH 1.0

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// File reading
char				*get_next_line(int fd);
char				*ft_read_and_save(int fd, char *save);
char				*ft_get_line(char *save);
char				*ft_save(char *save);
size_t				ft_strlen_gnl(char *s);
char				*ft_strchr_gnl(char *s, int c);
char				*ft_strjoin_gnl(char *s1, char *s2);

typedef struct s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			pitch;
}					t_player;

typedef struct s_data
{
	// Parsing
	mlx_texture_t	**textures;
	char			**texture_paths;
	char			**map_txt;
	int				map_height;
	char			orientation;
	int				yposition;
	int				xposition;

	// Event handler
	double			newposx;
	double			newposy;
	double			move_speed;

	// Raycasting
	mlx_texture_t	*tex;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	bool			hit;
	bool			side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	char			**map;

	// Textures
	uint32_t		floor;
	uint32_t		sky;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	mlx_image_t		*floor_img;
	mlx_texture_t	*floor_texture;
	mlx_image_t		*gun_img;
	double			wallx;
	int				texx;

	// MLX
	mlx_t			*mlx;
	int				window_width;
	int				window_height;
	t_player		player;
	int				is_resetting_pitch;
}					t_data;

// Main and initialization
void				init_data(t_data *data);
void				init_window(t_data *data);
void				error_msg_exit(char *msg, t_data *data);
int					main(int argc, char **argv);

// Parsing
int					parse_file(t_data *data, char *file);
int					parse_map(t_data *data, char **file_content, int i);
int					validate_map(t_data *data);
int					set_textures(t_data *data);

// Parsing map utils
void				count_map_dimensions(char **file_content, int start,
						int *width, int *height);
char				**create_map(char **file_content, int start, int width,
						int height);

// Map creation utils
typedef struct s_map_info
{
	int				start;
	int				width;
}					t_map_info;

typedef struct s_map_params
{
	char			**map;
	char			**file_content;
	int				i;
	int				start;
	int				width;
}					t_map_params;

void				fill_map_line(t_map_params *params);
void				init_map_params(t_map_params *params, char **file_content,
						char **map, t_map_info *info);
char				**allocate_map_memory(int height);
void				allocate_map_rows(char **map, int width, int height);
void				fill_map_content(t_map_params *params, int height);

// Parsing map validation utils
int					check_map_closure(char **map, int x, int y);
char				**copy_map(char **map);
void				set_player_direction(t_data *data);

// Parsing utils
int					check_file_extension(char *filename);
int					count_lines(char *file);
char				**read_file(char *file, int lines);
int					process_identifiers(t_data *data, char **file_content,
						int *i);

// Parsing identifiers
int					process_texture_identifier(t_data *data, char **line_split);
int					process_color_identifier(t_data *data, char **line_split);
int					init_texture_paths(t_data *data);
int					process_line(t_data *data, char **file_content, int *i);
int					check_all_identifiers(t_data *data);

typedef struct s_tex_info
{
	double			step;
	double			pos;
	int				num;
}					t_tex_info;

typedef struct s_wall_section
{
	t_data			*data;
	int				x;
	int				start;
	int				end;
	t_tex_info		*tex_info;
}					t_wall_section;

typedef struct s_wall_vars
{
	int				tex_y;
	uint32_t		color;
	double			wall_pos;
	int				pitch_offset;
}					t_wall_vars;

// Raycasting
void				render_frame(t_data *data);
void				get_step_for_check(t_data *data, int x);
void				calc_side_dist(t_data *data);
void				ft_dda(t_data *data);
void				ft_lineheight(t_data *data);
void				draw_line(t_data *data, int x);
uint32_t			get_texture_pixel(mlx_texture_t *texture, int x, int y);

// Raycasting sections
void				prepare_wall_drawing(t_data *data, t_tex_info *tex_info,
						int *bounds);
void				draw_ceiling_section(t_data *data, int x, int wall_start);
void				draw_wall_section(t_wall_section *section);
void				draw_floor_section(t_data *data, int x, int wall_end);

// Raycasting draw
void				draw_ceiling(t_data *data, int x, int y);
void				draw_floor(t_data *data, int x, int y);
double				calc_wall_position(t_data *data, int y, int pitch_offset);
void				draw_wall(t_data *data, int x, int y, t_tex_info *tex_info);

// Raycasting render
void				update_fps(t_data *data, int *frame_count,
						double *last_time, double *fps);
void				render_walls(t_data *data);

// Raycasting textures
void				prepare_texture_drawing(t_data *data, double *step,
						double *tex_pos);
int					get_texture_number(t_data *data);

// Raycasting floor
uint32_t			get_floor_color(t_data *data, int x, int y);
void				calc_ray_directions(t_data *data, float *ray_dir);
void				calc_floor_steps(t_data *data, float *ray_dir,
						float row_dist, float *floor_step);
void				get_floor_texture_coords(t_data *data, float *pos,
						int *tex_coords);

// No sky raycasting needed - using solid color

// Event handling
void				handle_key_press(mlx_key_data_t keydata, void *param);
void				check_keys(void *param);
void				check_basic_movement(t_data *data);

// Event handling - mouse
void				mouse_handler(double xpos, double ypos, void *param);
void				mouse_button_handler(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
void				debug_mouse_position(void *param);

// Event handling - movement
void				move_player(t_data *data, double dir);
void				strafe_player(t_data *data, double dir);
void				rotate_player(t_data *data, double dir);

// Event handling - position
int					is_valid_position(t_data *data, double x, double y);
int					check_padding_x(t_data *data, double x, double y);

typedef struct s_minimap
{
	int				map_size;
	int				tile_size;
	int				offset;
	int				player_size;
	int				width;
	int				height;
	int				max_x;
	int				max_y;
	int				map_width;
	int				map_height;
	int				min_x;
	int				player_x;
	int				player_y;
}					t_minimap;

// Minimap structures
typedef struct s_dir_params
{
	int				x;
	int				y;
	int				cell_size;
	int				map_size;
}					t_dir_params;

typedef struct s_indicator_data
{
	int				center_x;
	int				center_y;
}					t_indicator_data;

typedef struct s_cell_coords
{
	int				x;
	int				y;
	int				mini_x;
	int				mini_y;
}					t_cell_coords;

typedef struct s_cell_params
{
	int				x;
	int				y;
	int				mini_x;
	int				mini_y;
	int				cell_size;
	int				map_size;
	uint32_t		color;
}					t_cell_params;

typedef struct s_ray_params
{
	int				center_x;
	int				center_y;
	double			ray_angle;
	int				map_size;
}					t_ray_params;

typedef struct s_ray_segment_params
{
	int				width;
	int				map_size;
}					t_ray_segment_params;

typedef struct s_ray_data
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			dx;
	double			dy;
	int				ray_length;
	int				r;
	int				width;
	int				cx;
	int				cy;
}					t_ray_data;

typedef struct s_segment_data
{
	int				cx;
	int				cy;
	double			ray_angle;
}					t_segment_data;

typedef struct s_line_data
{
	int				dir_x;
	int				dir_y;
	int				center_x;
	int				center_y;
}					t_line_data;

typedef struct s_map_elem_vars
{
	int				x;
	int				y;
	t_cell_coords	coords;
}					t_map_elem_vars;

// Minimap functions
void				draw_map_2d(t_data *data);
void				init_minimap_params(t_minimap *mm, t_data *data);
void				init_minimap(t_minimap *mm, t_data *data);
void				draw_minimap_tile(t_data *data, t_minimap *mm, int x,
						int y);
void				draw_player_on_minimap(t_data *data, t_minimap *mm);
void				draw_map_cell(t_data *data, t_cell_coords *coords);
void				draw_player_dir_indicator(t_data *data, int x, int y,
						int cell_size);
void				draw_fov_rays(t_data *data, int center_x, int center_y,
						int map_size);
void				draw_fov_ray(t_data *data, int center_x, int center_y,
						t_ray_params *params);
void				draw_single_tile(t_data *data, t_minimap *mm, int x, int y);
void				draw_map_grid(t_data *data, t_minimap *mm);
int					get_tile_color(t_data *data, int x, int y);

typedef struct s_gun_info
{
	int				width;
	int				height;
	int				start_x;
	int				start_y;
}					t_gun_info;

// Gun and crosshair
void				init_gun(t_data *data);
void				draw_gun(t_data *data);
void				draw_crosshair(t_data *data);
void				draw_gun_barrel(t_data *data, t_gun_info *gun_info);
void				draw_gun_handle(t_data *data, t_gun_info *gun_info);

// Cleanup
void				clean_exit(t_data *data, int exit_code);
void				free_map(char **map);
void				free_textures(t_data *data);

// Cleanup utils
void				free_wall_textures(t_data *data);
void				free_other_textures(t_data *data);
void				free_texture_paths(t_data *data);

#endif