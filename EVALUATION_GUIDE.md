# Cub3D: A Comprehensive Guide

This document provides a complete explanation of the Cub3D project, from fundamental concepts to implementation details. It's designed to help anyone understand and explain the project, even without prior experience with raycasting or 3D graphics.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Raycasting Fundamentals](#raycasting-fundamentals)
3. [Project Structure](#project-structure)
4. [Executable Name](#executable-name)
5. [Configuration File](#configuration-file)
6. [Technical Elements of the Display](#technical-elements-of-the-display)
7. [User Basic Events](#user-basic-events)
8. [Movements](#movements)
9. [Walls and Textures](#walls-and-textures)
10. [Error Management](#error-management)
11. [Memory Management](#memory-management)
12. [Bonus Features](#bonus-features)
13. [Mathematical Concepts](#mathematical-concepts)
14. [Troubleshooting](#troubleshooting)
15. [Evaluation Tips](#evaluation-tips)

## Project Overview

### ELI5
Cub3D is like building a simple version of the very first 3D shooting games. You create a program that shows a maze from the player's point of view, where you can walk around using your keyboard and look around using your mouse. The walls have different pictures on them depending on which direction they're facing, and you can change these pictures by editing a special file.

### In-depth
Cub3D is a graphics project inspired by the groundbreaking game Wolfenstein 3D, which is widely considered the first successful first-person shooter (FPS) game. The project requires implementing a raycasting engine to create a 3D-like environment from a 2D map.

The core objectives include:
1. Creating a window that displays a 3D representation of a maze
2. Implementing player movement and rotation
3. Applying different textures to walls based on their orientation
4. Parsing a configuration file that defines textures, colors, and the map layout
5. Implementing proper error handling and memory management

The project serves as an introduction to graphics programming concepts such as raycasting, texture mapping, and event handling, while also reinforcing skills in file parsing, error management, and memory allocation.

## Raycasting Fundamentals

### ELI5
Imagine you're standing in a maze with a flashlight. You shine the light straight ahead and to the sides to see how far away the walls are. For each thin beam of light (or "ray"), you measure how far it travels before hitting a wall. The closer walls look taller, and farther walls look shorter. By shining many rays across your field of view and drawing what they hit, you create a 3D-looking picture of the maze.

### In-depth
Raycasting is a rendering technique that creates a 3D perspective from a 2D map by casting rays from the player's position and calculating their intersections with walls. Unlike full 3D rendering, raycasting is computationally efficient while still creating a convincing 3D effect.

Here's how the raycasting algorithm works in Cub3D:

1. **Map Representation**:
   - The maze is represented as a 2D grid/array
   - Each cell contains either a wall (1) or empty space (0)
   - The player has a position (x, y) and a direction vector

2. **Ray Casting Process**:
   - For each vertical column of the screen:
     - Calculate the ray direction based on the player's direction and the camera plane
     - Determine which grid cell the ray is in
     - Calculate the distance to the next x-side and y-side of the grid
     - Perform a DDA (Digital Differential Analysis) algorithm to find the first wall hit
     - Calculate the perpendicular distance to the wall to avoid fisheye effect
     - Determine the height of the wall slice to draw

3. **Texture Mapping**:
   - Calculate which part of the texture to use based on where the ray hit the wall
   - Apply the texture to the wall slice
   - Different textures are used depending on the wall's orientation (N, S, E, W)

4. **Rendering**:
   - Draw the ceiling with a solid color
   - Draw the textured wall slice
   - Draw the floor with a solid color or texture

The key mathematical components include vector operations, ray-plane intersections, and perspective projection. The algorithm is optimized to only perform calculations for visible walls, making it efficient even on older hardware.

Here's a simplified code example of the core raycasting loop:

```c
for (int x = 0; x < screenWidth; x++) {
    // Calculate ray position and direction
    double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // Which box of the map we're in
    int mapX = (int)posX;
    int mapY = (int)posY;

    // Length of ray from current position to next x or y-side
    double sideDistX, sideDistY;

    // Length of ray from one x or y-side to next x or y-side
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // Calculate step and initial sideDist
    int stepX, stepY;
    int hit = 0; // was there a wall hit?
    int side; // was a NS or a EW wall hit?

    // Perform DDA
    while (hit == 0) {
        // Jump to next map square
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
    }

    // Calculate distance projected on camera direction
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

    // Calculate height of line to draw on screen
    int lineHeight = (int)(screenHeight / perpWallDist);

    // Draw the walls
    drawLine(x, lineHeight, side);
}
```

## Project Structure

### ELI5
Our game is like a big machine with different parts that work together. There's a part that reads the map, a part that draws the walls, a part that moves the player, and so on. Each part has its own job, but they all talk to each other to make the game work.

### In-depth
The Cub3D project is organized into several modules, each responsible for a specific aspect of the game:

1. **Main Module** (`main.c`):
   - Entry point of the program
   - Initializes the game data structure
   - Sets up the MLX library
   - Starts the game loop

2. **Parsing Module** (`parsing.c`, `parsing_map.c`):
   - Reads and validates the configuration file
   - Loads textures from specified paths
   - Parses the map layout
   - Validates map integrity (enclosed by walls, single player position)

3. **Raycasting Module** (`raycasting.c`):
   - Implements the core raycasting algorithm
   - Renders walls with textures
   - Handles floor and ceiling rendering

4. **Event Handling Module** (`event_handler.c`):
   - Processes keyboard and mouse input
   - Updates player position and orientation
   - Handles window events (close, resize)

5. **Cleanup Module** (`cleanup.c`):
   - Frees allocated memory
   - Destroys textures and images
   - Closes the MLX window

6. **Bonus Features** (`gun_simple.c`):
   - Implements additional features like weapon display

The project uses the following key data structures:

```c
typedef struct s_data
{
    void        *mlx;           // MLX instance
    void        *window;        // Window pointer
    int         window_width;   // Window width
    int         window_height;  // Window height
    char        **map;          // 2D array representing the map
    int         map_width;      // Map width
    int         map_height;     // Map height
    char        *texture_paths[4]; // Paths to wall textures (N,S,E,W)
    mlx_texture_t *textures[4]; // Wall textures
    mlx_texture_t *floor_texture; // Floor texture
    uint32_t    floor;          // Floor color
    uint32_t    sky;            // Ceiling color
    t_player    player;         // Player data
    void        *gun_img;       // Gun image (bonus)
} t_data;

typedef struct s_player
{
    double      posx;           // Player X position
    double      posy;           // Player Y position
    double      dirx;           // Direction vector X
    double      diry;           // Direction vector Y
    double      planex;         // Camera plane X
    double      planey;         // Camera plane Y
    double      move_speed;     // Movement speed
    double      rot_speed;      // Rotation speed
} t_player;
```

The project follows a modular design pattern, with clear separation of concerns between different components. This makes the code more maintainable and easier to understand.

## Executable Name

### ELI5
Our program is called "cub3d" (lowercase), just like the subject asks. When you type "make", it creates this program without any errors or warnings.

### In-depth
The Makefile is configured to compile the project with the name "cub3d". It uses the flags `-Wall -Werror -Wextra` as required by the subject. The compilation process includes:

1. Compiling the libft library (a custom library with utility functions)
2. Compiling the MLX42 library (a graphics library for window management and rendering)
3. Compiling all the source files with optimization flags (-O3)
4. Linking everything together to create the executable

The Makefile includes the standard rules:
- `all`: Default rule that builds the executable
- `clean`: Removes object files
- `fclean`: Removes object files and the executable
- `re`: Performs a clean rebuild

The compilation is set up to avoid re-linking, meaning it only recompiles files that have been modified since the last compilation. This is achieved through proper dependency tracking in the Makefile.

Here's a snippet from the Makefile:

```makefile
NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g -I includes

SRC_DIR = src
OBJ_DIR = bin

SRC_FILES = main.c cleanup.c event_handler.c parsing.c parsing_map.c raycasting.c get_next_line.c gun_simple.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(OBJ) -Llibft -lft -L./MLX42/build -lmlx42 -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "cub3d successfully compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ./include -I ./MLX42/include

clean:
	@make -C libft clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed!"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "cub3d removed!"

re: fclean all
```

The executable name "cub3D" is a reference to the original game Wolfenstein 3D, with "cub" representing a cube or 3D space.

## Configuration File

### ELI5
Our game reads a special file (like a recipe) that tells it what pictures to use for the walls, what colors to use for the floor and ceiling, and what the maze looks like. If this file has mistakes, the game tells you what's wrong instead of crashing.

### In-depth
The configuration file parser in `parsing.c` handles all the required elements as specified in the subject:

1. **Texture Paths**:
   - North texture (NO): `NO ./path_to_the_north_texture`
   - South texture (SO): `SO ./path_to_the_south_texture`
   - East texture (EA): `EA ./path_to_the_east_texture`
   - West texture (WE): `WE ./path_to_the_west_texture`

2. **Colors**:
   - Floor color (F): `F R,G,B` (e.g., `F 220,100,0`)
   - Ceiling color (C): `C R,G,B` (e.g., `C 225,30,0`)

3. **Map**:
   - Composed of characters: 0 (empty space), 1 (wall), and N/S/E/W (player position and orientation)
   - The map must be surrounded by walls (1s)
   - The map must contain exactly one player position

Here's an example of a valid configuration file:

```
NO ./textures/wallmonkey.png
SO ./textures/wallmonkey.png
WE ./textures/wallmonkey.png
EA ./textures/wallmonkey.png

F 70,70,80
C 30,30,30

111111111111111111111
100000000000000000001
100000000000000000001
100000000000000000001
100000111110000000001
100000100010000000001
100000100010000000001
100000100010000000001
100000111110000000001
100000000000000000001
100000000000000000001
100000000N00000000001
100000000000000000001
100000000000000000001
111111111111111111111
```

The parser performs extensive error checking:

1. **File Validation**:
   - Checks if the file exists
   - Validates file extension (.cub)
   - Ensures the file is readable

2. **Identifier Validation**:
   - Checks for missing identifiers (NO, SO, WE, EA, F, C)
   - Detects duplicate identifiers
   - Validates the format of each identifier line

3. **Texture Validation**:
   - Verifies that texture paths point to existing files
   - Ensures textures can be loaded by the MLX library
   - Supports both relative and absolute paths

4. **Color Validation**:
   - Ensures RGB values are in the valid range (0-255)
   - Checks for proper comma separation
   - Converts RGB values to a 32-bit color format

5. **Map Validation**:
   - Ensures the map is properly enclosed by walls
   - Checks for invalid characters
   - Verifies there is exactly one player position
   - Handles spaces in the map correctly

When an error is detected, the program prints a specific error message and exits with a non-zero status code. The error messages are designed to be informative, helping the user identify and fix the issue.

Here's a simplified version of the parsing algorithm:

```c
int parse_file(t_data *data, char *file)
{
    // Check file extension
    if (check_file_extension(file))
        return (error("Invalid file extension"));

    // Read file content
    char **file_content = read_file(file, count_lines(file));
    if (!file_content)
        return (error("Failed to read file"));

    // Process identifiers (NO, SO, WE, EA, F, C)
    int i = 0;
    if (process_identifiers(data, file_content, &i))
        return (error("Invalid identifiers"));

    // Parse map
    if (parse_map(data, file_content, i))
        return (error("Invalid map"));

    // Load textures
    if (set_textures(data))
        return (error("Failed to load textures"));

    return (0);
}
```

The configuration file parser is robust and handles a wide range of edge cases, ensuring the game starts with valid data or provides clear error messages.

## Technical Elements of the Display

### ELI5
When you start our game, a window opens showing a 3D maze from the player's view. The window works properly - you can move it around, minimize it, and maximize it, and the game keeps working correctly without breaking.

### In-depth
The display is implemented using the MLX42 library, which provides a cross-platform interface for creating windows and rendering graphics.

1. **Window Creation and Management**:
   - The window is created in `main.c` using `mlx_init()` with a specified width and height (typically 1280x720)
   - The window title is set to "cub3D"
   - Event hooks are registered for window events (close, resize, etc.)
   - The window properly handles minimizing, maximizing, and moving
   - The content remains consistent when the window is manipulated

2. **Rendering Pipeline**:
   - The rendering is done in a continuous loop using `mlx_loop_hook()`
   - Each frame, the raycasting algorithm renders the scene
   - Double buffering is used to prevent flickering
   - The frame rate is controlled to ensure smooth performance

3. **Image Handling**:
   - The main display is an MLX image that gets updated each frame
   - Wall textures are loaded as PNG files using `mlx_load_png()`
   - The floor texture (galaxy_floors.png) is also loaded as a PNG
   - Pixel manipulation is done using `mlx_put_pixel()` for efficient rendering

Here's a simplified version of the main rendering loop:

```c
void game_loop(void *param)
{
    t_data *data = (t_data *)param;

    // Clear the screen
    clear_image(data->img);

    // Perform raycasting
    raycasting(data);

    // Draw additional elements (gun, etc.)
    draw_gun(data);

    // Update the display
    mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

int main(int argc, char **argv)
{
    t_data data;

    // Initialize data structure
    init_data(&data);

    // Parse configuration file
    if (parse_file(&data, argv[1]))
        return (1);

    // Initialize MLX
    data.mlx = mlx_init(data.window_width, data.window_height, "cub3D", false);
    if (!data.mlx)
        return (1);

    // Set up hooks
    mlx_key_hook(data.mlx, key_handler, &data);
    mlx_close_hook(data.mlx, close_handler, &data);
    mlx_loop_hook(data.mlx, game_loop, &data);

    // Start the game loop
    mlx_loop(data.mlx);

    // Cleanup
    cleanup(&data);

    return (0);
}
```

The technical implementation ensures that the window behaves correctly in all situations, including when it's partially obscured, minimized, or moved. This is achieved through proper event handling and a robust rendering pipeline.

## User Basic Events

### ELI5
Our game responds to your actions:
- If you click the X button on the window, the game closes nicely
- If you press ESC, the game also closes nicely
- If you press the WASD keys, you can move around in the maze
- If you move the mouse, you can look around

### In-depth
User input is handled through the MLX42 library's event system in `event_handler.c`. The implementation follows the observer pattern, where callback functions are registered to respond to specific events.

1. **Window Close Event**:
   - The red cross (X) button is handled by registering a callback function with `mlx_close_hook()`
   - When triggered, the function calls `mlx_close_window()` and ensures proper cleanup
   - The cleanup process frees all allocated memory and resources

   ```c
   void close_handler(void *param)
   {
       t_data *data = (t_data *)param;

       // Free resources and exit
       cleanup(data);
       exit(0);
   }
   ```

2. **Keyboard Events**:
   - Keyboard input is handled by registering a callback function with `mlx_key_hook()`
   - The ESC key (keycode 53) triggers a clean exit
   - Movement keys (W, A, S, D) update the player's position or orientation
   - The key handler checks for key presses and releases to enable smooth movement

   ```c
   void key_handler(mlx_key_data_t keydata, void *param)
   {
       t_data *data = (t_data *)param;

       // Handle ESC key
       if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
           mlx_close_window(data->mlx);

       // Handle movement keys
       if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
           move_forward(data);
       if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
           move_backward(data);
       if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
           move_left(data);
       if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
           move_right(data);
       if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
           rotate_left(data);
       if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
           rotate_right(data);
   }
   ```

3. **Mouse Events** (Bonus):
   - Mouse movement is captured using `mlx_mouse_hook()`
   - The change in mouse position is used to rotate the player's view
   - This creates a more intuitive and immersive first-person experience

   ```c
   void mouse_handler(double xpos, double ypos, void *param)
   {
       t_data *data = (t_data *)param;
       static double last_x = -1;

       if (last_x == -1)
           last_x = xpos;

       // Calculate mouse movement and rotate view
       double delta_x = xpos - last_x;
       rotate_view(data, delta_x * data->player.rot_speed * 0.1);

       last_x = xpos;
   }
   ```

The event system is non-blocking, allowing the game to continue running while waiting for user input. This creates a smooth and responsive user experience, where the game reacts immediately to user actions.

## Movements

### ELI5
In our game, you can move around like in a real 3D world:
- The game starts with you facing the direction shown in the map (N, S, E, or W)
- You can look left and right using the arrow keys
- You can walk forward and backward using W and S
- You can step sideways using A and D
- All these movements are smooth and feel natural

### In-depth
The movement system is implemented in `event_handler.c` and uses vector mathematics to calculate the player's position and orientation:

1. **Player Orientation**:
   - The player's initial orientation is determined by the character in the map (N, S, E, W)
   - N (North): Direction vector (0, -1), Plane vector (0.66, 0)
   - S (South): Direction vector (0, 1), Plane vector (-0.66, 0)
   - E (East): Direction vector (1, 0), Plane vector (0, 0.66)
   - W (West): Direction vector (-1, 0), Plane vector (0, -0.66)

   ```c
   void init_player_direction(t_data *data, char direction)
   {
       if (direction == 'N') {
           data->player.dirx = 0;
           data->player.diry = -1;
           data->player.planex = 0.66;
           data->player.planey = 0;
       } else if (direction == 'S') {
           data->player.dirx = 0;
           data->player.diry = 1;
           data->player.planex = -0.66;
           data->player.planey = 0;
       } else if (direction == 'E') {
           data->player.dirx = 1;
           data->player.diry = 0;
           data->player.planex = 0;
           data->player.planey = 0.66;
       } else if (direction == 'W') {
           data->player.dirx = -1;
           data->player.diry = 0;
           data->player.planex = 0;
           data->player.planey = -0.66;
       }
   }
   ```

2. **Rotation**:
   - Left/right rotation is implemented by applying a rotation matrix to both the direction and plane vectors
   - The rotation speed is controlled by a constant to ensure smooth movement
   - The formula used is:
     ```
     newDirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed)
     newDirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed)
     ```
     (Similar for the plane vector)

   ```c
   void rotate_right(t_data *data)
   {
       double old_dirx = data->player.dirx;
       data->player.dirx = data->player.dirx * cos(-data->player.rot_speed) -
                           data->player.diry * sin(-data->player.rot_speed);
       data->player.diry = old_dirx * sin(-data->player.rot_speed) +
                           data->player.diry * cos(-data->player.rot_speed);
       double old_planex = data->player.planex;
       data->player.planex = data->player.planex * cos(-data->player.rot_speed) -
                             data->player.planey * sin(-data->player.rot_speed);
       data->player.planey = old_planex * sin(-data->player.rot_speed) +
                             data->player.planey * cos(-data->player.rot_speed);
   }
   ```

3. **Forward/Backward Movement**:
   - Forward movement adds the direction vector (scaled by move speed) to the player's position
   - Backward movement subtracts the direction vector
   - Collision detection is performed to prevent moving into walls

   ```c
   void move_forward(t_data *data)
   {
       double new_x = data->player.posx + data->player.dirx * data->player.move_speed;
       double new_y = data->player.posy + data->player.diry * data->player.move_speed;

       // Check for collision
       if (data->map[(int)new_y][(int)data->player.posx] != '1')
           data->player.posy = new_y;
       if (data->map[(int)data->player.posy][(int)new_x] != '1')
           data->player.posx = new_x;
   }
   ```

4. **Lateral Movement**:
   - Left/right movement adds/subtracts the perpendicular of the direction vector
   - The perpendicular is calculated by rotating the direction vector by 90 degrees
   - Collision detection is also applied here

   ```c
   void move_left(t_data *data)
   {
       double new_x = data->player.posx - data->player.planey * data->player.move_speed;
       double new_y = data->player.posy + data->player.planex * data->player.move_speed;

       // Check for collision
       if (data->map[(int)new_y][(int)data->player.posx] != '1')
           data->player.posy = new_y;
       if (data->map[(int)data->player.posy][(int)new_x] != '1')
           data->player.posx = new_x;
   }
   ```

5. **Collision Detection**:
   - Before updating the player's position, the code checks if the new position would be inside a wall
   - If a collision is detected, the movement is prevented
   - The collision detection has a small margin to prevent getting too close to walls

The movement system is frame-rate independent, ensuring consistent speed regardless of the system's performance. This is achieved by scaling the movement and rotation speeds based on the time elapsed since the last frame.

## Walls and Textures

### ELI5
The walls in our game look different depending on which way they're facing:
- North walls have one texture
- South walls have another texture
- East and West walls have their own textures too
- If you change the texture files in the configuration, the walls look different the next time you run the game
- The floor and ceiling have the colors you specify in the configuration file

### In-depth
The wall rendering system is implemented in `raycasting.c` and uses the following techniques:

1. **Texture Mapping**:
   - Each wall direction (N, S, E, W) has its own texture loaded from the paths specified in the configuration file
   - The textures are loaded using `mlx_load_png()` and stored in the game data structure
   - During raycasting, the wall orientation is determined by which side of the grid cell was hit
   - The appropriate texture is selected based on this orientation

   ```c
   // Determine which texture to use based on wall orientation
   int tex_num;
   if (side == 0 && ray_dir_x > 0) tex_num = 0; // East
   else if (side == 0 && ray_dir_x < 0) tex_num = 1; // West
   else if (side == 1 && ray_dir_y > 0) tex_num = 2; // South
   else tex_num = 3; // North
   ```

2. **Texture Coordinate Calculation**:
   - The exact hit position on the wall is calculated to determine the x-coordinate in the texture
   - For vertical walls (E/W), the x-coordinate is the fractional part of the y-position
   - For horizontal walls (N/S), the x-coordinate is the fractional part of the x-position
   - The y-coordinate is calculated based on the height of the wall on the screen

   ```c
   // Calculate exact hit position
   double wall_x;
   if (side == 0) wall_x = player_pos_y + perp_wall_dist * ray_dir_y;
   else wall_x = player_pos_x + perp_wall_dist * ray_dir_x;
   wall_x -= floor(wall_x);

   // Calculate texture coordinates
   int tex_x = (int)(wall_x * texture_width);
   if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
       tex_x = texture_width - tex_x - 1;
   ```

3. **Perspective Correction**:
   - The distance to the wall is calculated using the perpendicular distance to avoid the fisheye effect
   - This distance is used to determine the height of the wall on the screen
   - The formula is: `lineHeight = (int)(window_height / perpWallDist)`

   ```c
   // Calculate distance to the wall
   double perp_wall_dist;
   if (side == 0)
       perp_wall_dist = (map_x - player_pos_x + (1 - step_x) / 2) / ray_dir_x;
   else
       perp_wall_dist = (map_y - player_pos_y + (1 - step_y) / 2) / ray_dir_y;

   // Calculate height of the wall slice
   int line_height = (int)(window_height / perp_wall_dist);
   ```

4. **Drawing the Wall Slice**:
   - For each vertical slice of the screen, a corresponding slice of the texture is drawn
   - The texture is scaled to match the height of the wall on the screen
   - The color is darkened for walls hit on the side (E/W) to create a shadow effect

   ```c
   // Calculate start and end positions for drawing
   int draw_start = -line_height / 2 + window_height / 2;
   if (draw_start < 0) draw_start = 0;
   int draw_end = line_height / 2 + window_height / 2;
   if (draw_end >= window_height) draw_end = window_height - 1;

   // Draw the wall slice
   for (int y = draw_start; y < draw_end; y++) {
       int tex_y = (y - draw_start) * texture_height / (draw_end - draw_start);
       uint32_t color = get_texture_pixel(textures[tex_num], tex_x, tex_y);

       // Make sides darker for shadow effect
       if (side == 1) color = (color >> 1) & 8355711;

       mlx_put_pixel(img, x, y, color);
   }
   ```

5. **Floor and Ceiling Rendering**:
   - The floor and ceiling are rendered with the colors specified in the configuration file
   - The floor texture (galaxy_floors.png) is applied using a similar technique to the wall textures
   - Ray casting is used to determine the texture coordinates for each pixel

The system correctly handles texture changes in the configuration file and reports errors for non-existent textures. The textures are loaded at startup and stored in memory for efficient rendering during gameplay.

## Error Management

### ELI5
Our program is very careful about errors:
- If you try to run it with wrong information, it tells you what's wrong
- It doesn't waste memory - it cleans up after itself
- It doesn't crash even if you press random keys
- If you change the map to something invalid, it tells you what's wrong instead of crashing

### In-depth
The error management system is comprehensive and handles various types of errors:

1. **Input Validation**:
   - Command-line arguments are validated to ensure the correct number and format
   - The configuration file is thoroughly checked for syntax and semantic errors
   - All error messages are specific and informative, indicating the exact nature of the problem

   ```c
   int main(int argc, char **argv)
   {
       // Check number of arguments
       if (argc != 2)
           return (error("Usage: ./cub3d <map.cub>"));

       // Check file extension
       if (check_file_extension(argv[1]))
           return (error("Invalid file extension. Expected .cub"));

       // Initialize and parse
       t_data data;
       init_data(&data);
       if (parse_file(&data, argv[1]))
           return (1); // Error message already printed

       // Continue with game initialization
       // ...
   }
   ```

2. **Memory Management**:
   - All dynamically allocated memory is tracked and properly freed
   - The cleanup function in `cleanup.c` ensures that all resources are released
   - Memory leaks are prevented by careful allocation and deallocation
   - The program has been tested with valgrind to verify the absence of memory leaks

   ```c
   void cleanup(t_data *data)
   {
       // Free map data
       if (data->map)
       {
           for (int i = 0; i < data->map_height; i++)
               free(data->map[i]);
           free(data->map);
           data->map = NULL;
       }

       // Free texture paths
       for (int i = 0; i < 4; i++)
       {
           if (data->texture_paths[i])
               free(data->texture_paths[i]);
       }

       // Delete textures
       for (int i = 0; i < 4; i++)
       {
           if (data->textures[i])
               mlx_delete_texture(data->textures[i]);
       }

       // Delete floor texture
       if (data->floor_texture)
           mlx_delete_texture(data->floor_texture);

       // Delete gun image
       if (data->gun_img)
           mlx_delete_image(data->mlx, data->gun_img);

       // Terminate MLX
       if (data->mlx)
           mlx_terminate(data->mlx);
   }
   ```

3. **Robust Input Handling**:
   - The input system is designed to handle unexpected key combinations
   - Random key presses do not cause crashes or unexpected behavior
   - The event loop continues to function normally even with erratic input

4. **Map Validation**:
   - The map parser in `parsing_map.c` performs extensive validation
   - It checks for proper wall enclosure, valid characters, and a single player position
   - If the map is modified to an invalid state, the program detects this and reports the specific error
   - The validation is thorough enough to catch subtle issues like gaps in the walls

   ```c
   int validate_map(t_data *data)
   {
       // Check for player position
       int player_count = 0;
       for (int y = 0; y < data->map_height; y++)
       {
           for (int x = 0; x < data->map_width; x++)
           {
               if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
                   data->map[y][x] == 'E' || data->map[y][x] == 'W')
               {
                   player_count++;
                   data->player.posx = x + 0.5;
                   data->player.posy = y + 0.5;
                   init_player_direction(data, data->map[y][x]);
                   data->map[y][x] = '0'; // Replace with empty space
               }
               else if (data->map[y][x] != '0' && data->map[y][x] != '1' &&
                        data->map[y][x] != ' ')
                   return (error("Invalid character in map"));
           }
       }

       if (player_count != 1)
           return (error("Map must contain exactly one player position"));

       // Check if map is enclosed by walls
       if (check_map_enclosed(data))
           return (error("Map is not properly enclosed by walls"));

       return (0);
   }
   ```

5. **Graceful Termination**:
   - When an error is detected, the program prints a specific error message
   - It then performs proper cleanup to free all allocated resources
   - Finally, it exits with a non-zero status code to indicate failure

The error management system ensures that the program behaves predictably and gracefully in all situations, providing clear feedback to the user when problems occur. This makes the program robust and user-friendly, even when faced with unexpected inputs or configurations.

## Memory Management

### ELI5
Our program is like a tidy person who always cleans up after itself. It only uses the memory it needs, and when it's done with something, it puts it away properly. This means the program doesn't slow down your computer or crash because of memory problems.

### In-depth
Memory management is a critical aspect of the Cub3D project, as improper memory handling can lead to leaks, segmentation faults, and other runtime issues. Our implementation follows best practices for memory management in C:

1. **Allocation Tracking**:
   - All dynamically allocated memory is carefully tracked
   - Each allocation is paired with a corresponding deallocation
   - Pointers are set to NULL after freeing to prevent double-free errors

2. **Cleanup Function**:
   - The `cleanup.c` file contains a comprehensive cleanup function
   - This function is called at program exit, whether normal or due to an error
   - It systematically frees all allocated resources in the correct order

3. **Resource Management**:
   - Textures are loaded once and reused throughout the program
   - The MLX library resources (window, images) are properly terminated
   - File handles are closed after use

4. **Error Recovery**:
   - If an error occurs during initialization, partial cleanup is performed
   - This prevents memory leaks even in error conditions
   - The cleanup process is robust against NULL pointers and uninitialized data

5. **Testing**:
   - The program has been tested with valgrind to verify the absence of memory leaks
   - Memory usage remains stable during extended gameplay
   - No memory-related crashes or errors occur

The memory management system ensures that the program runs efficiently and reliably, without consuming excessive resources or leaking memory over time.

## Bonus Features

### ELI5
We've added some extra cool things to our game that weren't required:
- The walls stop you from walking through them (collision detection)
- You can look around using the mouse, just like in real first-person games
- We added a gun that shows up at the bottom of the screen

### In-depth
The following bonus features have been implemented to enhance the gameplay experience:

1. **Wall Collisions**:
   - Implemented in `event_handler.c`
   - Before updating the player's position, the code checks if the new position would be inside a wall
   - If a collision is detected, the movement is prevented
   - The collision detection has a small margin to prevent getting too close to walls

   ```c
   void move_forward(t_data *data)
   {
       double new_x = data->player.posx + data->player.dirx * data->player.move_speed;
       double new_y = data->player.posy + data->player.diry * data->player.move_speed;

       // Check for collision
       if (data->map[(int)new_y][(int)data->player.posx] != '1')
           data->player.posy = new_y;
       if (data->map[(int)data->player.posy][(int)new_x] != '1')
           data->player.posx = new_x;
   }
   ```

2. **Mouse Rotation**:
   - Implemented by registering a mouse callback function with `mlx_mouse_hook()`
   - The mouse position is tracked, and changes in the x-coordinate rotate the player's view
   - The sensitivity is adjustable through a constant
   - The implementation feels natural and intuitive, similar to commercial first-person games

   ```c
   void mouse_handler(double xpos, double ypos, void *param)
   {
       t_data *data = (t_data *)param;
       static double last_x = -1;

       if (last_x == -1)
           last_x = xpos;

       // Calculate mouse movement and rotate view
       double delta_x = xpos - last_x;
       rotate_view(data, delta_x * data->player.rot_speed * 0.1);

       last_x = xpos;
   }
   ```

3. **Gun Display**:
   - Implemented in `gun_simple.c`
   - A gun texture (gunhehe.png) is loaded and displayed at the bottom of the screen
   - The gun is positioned slightly to the left of center for a more realistic first-person view
   - The gun is rendered on top of the 3D scene to create a first-person shooter feel

   ```c
   void init_gun(t_data *data)
   {
       mlx_texture_t *gun_texture;
       int gun_width, gun_height;

       // Load gun texture
       gun_texture = mlx_load_png("./textures/gunhehe.png");
       if (!gun_texture)
       {
           printf("Failed to load gun texture, using simple gun instead\n");
           return;
       }

       // Create gun image
       gun_width = 250;
       gun_height = 170;
       data->gun_img = mlx_new_image(data->mlx, gun_width, gun_height);

       // Copy texture to image
       for (int y = 0; y < gun_height; y++)
       {
           for (int x = 0; x < gun_width; x++)
           {
               int tex_x = x * gun_texture->width / gun_width;
               int tex_y = y * gun_texture->height / gun_height;
               uint32_t color = get_texture_pixel(gun_texture, tex_x, tex_y);
               mlx_put_pixel(data->gun_img, x, y, color);
           }
       }

       // Position gun at the bottom center, shifted 15% to the left for a more realistic POV
       int center_x = data->window_width / 2;
       int offset_x = center_x * 0.15; // 15% left from center

       mlx_image_to_window(data->mlx, data->gun_img,
           center_x - (gun_width / 2) - offset_x,
           data->window_height - gun_height);

       // Free texture
       mlx_delete_texture(gun_texture);
   }
   ```

These bonus features enhance the gameplay experience and demonstrate a deeper understanding of the project's concepts. They make the game more immersive and enjoyable to play.

## Mathematical Concepts

### ELI5
Our game uses math to create a 3D-looking world from a 2D map. It's like using a ruler and compass to draw a picture that looks real. The math helps figure out how tall walls should look, what color each pixel should be, and how to move around in the maze.

### In-depth
The Cub3D project relies on several key mathematical concepts to create its 3D perspective:

1. **Vector Mathematics**:
   - Vectors are used to represent the player's position, direction, and camera plane
   - Vector operations (addition, subtraction, scaling) are used for movement
   - The dot product is used for calculating perpendicular distances

2. **Trigonometry**:
   - Sine and cosine functions are used for rotation
   - The rotation matrix is applied to both the direction and plane vectors
   - Arctangent is used for calculating angles

3. **Ray-Plane Intersection**:
   - The DDA (Digital Differential Analysis) algorithm is used to efficiently find ray-wall intersections
   - This algorithm works by stepping through the grid cells that the ray passes through
   - It's more efficient than checking every cell in the map

4. **Perspective Projection**:
   - The distance to walls is used to calculate their apparent height on the screen
   - The formula is: `lineHeight = (int)(window_height / perpWallDist)`
   - This creates the illusion of depth and perspective

5. **Texture Mapping**:
   - Affine texture mapping is used to apply textures to walls
   - The exact hit position on the wall determines the x-coordinate in the texture
   - The y-coordinate is calculated based on the height of the wall on the screen

6. **Collision Detection**:
   - Vector mathematics is used to predict the player's next position
   - This position is checked against the map to detect collisions
   - Separate checks are performed for x and y components to allow sliding along walls

These mathematical concepts work together to create a convincing 3D perspective from a 2D map, which is the core of the raycasting technique used in Cub3D.

## Troubleshooting

### ELI5
Sometimes things go wrong when running the game. Here are some common problems and how to fix them:
- If the game doesn't start, check if your map file is correct
- If textures don't show up, make sure the texture files exist in the right place
- If the game is slow, try using a simpler map or smaller textures

### In-depth
Here are some common issues that might arise during evaluation and how to address them:

1. **Compilation Issues**:
   - **Problem**: The program fails to compile
   - **Solution**: Ensure all dependencies are installed (MLX42, GLFW)
   - **Command**: `sudo apt-get install libglfw3 libglfw3-dev`

2. **Missing Textures**:
   - **Problem**: Textures don't appear or the program reports missing textures
   - **Solution**: Verify that the texture paths in the configuration file are correct
   - **Check**: Use relative paths (`./textures/wallmonkey.png`) or absolute paths

3. **Map Validation Errors**:
   - **Problem**: The program reports that the map is invalid
   - **Solution**: Check that the map is properly enclosed by walls and has exactly one player position
   - **Example**: Use the provided `maps/relative.cub` as a reference for a valid map

4. **Performance Issues**:
   - **Problem**: The game runs slowly or has low frame rate
   - **Solution**: Reduce the window size or use smaller textures
   - **Setting**: Modify the window dimensions in `main.c` (e.g., 800x600 instead of 1280x720)

5. **Memory Leaks**:
   - **Problem**: The program leaks memory
   - **Solution**: Run with valgrind to identify the source of the leak
   - **Command**: `valgrind --leak-check=full ./cub3d maps/relative.cub`

6. **Input Issues**:
   - **Problem**: Keyboard or mouse input doesn't work as expected
   - **Solution**: Check the key handling in `event_handler.c`
   - **Note**: Different keyboard layouts might affect key mappings

7. **Window Management**:
   - **Problem**: The window doesn't respond to events (minimize, close)
   - **Solution**: Ensure the MLX hooks are properly registered
   - **Check**: Look for `mlx_close_hook()` and other event registrations in `main.c`

If you encounter any other issues, the error messages provided by the program should give you a good starting point for troubleshooting. The code is well-commented and follows a logical structure, making it easier to identify and fix problems.

## Evaluation Tips

### ELI5
When someone is checking your game, they'll look at a few important things:
- Does the game start and show a 3D maze?
- Can you move around using the keyboard?
- Do the walls have different textures depending on which way they're facing?
- Does the game handle errors properly?

### In-depth
Here are some tips for evaluating the Cub3D project according to the evaluation sheet:

1. **Executable Name**:
   - Verify that the executable is named `cub3D`
   - Check that it compiles without errors using `make`
   - Ensure there are no re-linking issues

2. **Configuration File**:
   - Test with various configuration files to ensure all elements are configurable
   - Verify that the program handles errors in the configuration file
   - Check that the file extension validation works (only .cub files are accepted)

3. **Technical Elements of the Display**:
   - Verify that a window opens when the program starts
   - Check that the maze is displayed correctly
   - Test window management (minimize, maximize, move)

4. **User Basic Events**:
   - Test the red cross button to ensure it closes the window
   - Verify that the ESC key exits the program
   - Test the movement keys (WASD) to ensure they work correctly

5. **Movements**:
   - Test each cardinal orientation (N, S, E, W) to ensure the player spawns correctly
   - Verify that the arrow keys rotate the view
   - Test forward/backward movement with W/S
   - Test lateral movement with A/D
   - Check that the movement is smooth and responsive

6. **Walls**:
   - Verify that wall textures vary based on orientation
   - Test changing texture paths in the configuration file
   - Check that floor and ceiling colors are handled correctly

7. **Error Management**:
   - Test with invalid arguments
   - Check for memory leaks using valgrind
   - Test with random key presses
   - Modify the map to test error handling

8. **Bonus Features** (if applicable):
   - Test wall collisions
   - Verify that the minimap works (if implemented)
   - Test doors (if implemented)
   - Check for animated sprites (if implemented)
   - Test mouse rotation

Remember that the mandatory part must be perfect before considering the bonus features. Take your time to thoroughly test each aspect of the project, and don't hesitate to ask questions if something is unclear.

4. **Libraries**:
   - **MLX42**: Used for window management, rendering, and input handling
   - **libft**: Custom library with various utility functions

5. **Performance Optimizations**:
   - Efficient raycasting algorithm with early termination
   - Texture caching to avoid redundant calculations
   - Frame-rate independent movement for consistent gameplay
   - Compiler optimizations (-O3) for better performance

The implementation follows good software engineering practices, with clear separation of concerns, meaningful variable names, and comprehensive error handling.

---

This guide should help you understand the technical aspects of the Cub3D project and answer any questions that might arise during the evaluation. If you have any specific questions not covered here, feel free to ask!
