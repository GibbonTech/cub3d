# cub3D: A Raycasting Engine

## Table of Contents
1. [Introduction to Raycasting](#introduction-to-raycasting)
2. [Project Structure](#project-structure)
3. [Core Components](#core-components)
   - [Parsing](#parsing)
   - [Initialization](#initialization)
   - [Raycasting](#raycasting)
   - [Input Handling](#input-handling)
   - [Rendering](#rendering)
   - [Minimap](#minimap)
   - [Utilities](#utilities)
4. [How Raycasting Works](#how-raycasting-works)
5. [Map Format](#map-format)
6. [Testing Guide](#testing-guide)
7. [Common Issues](#common-issues)

## Introduction to Raycasting

Raycasting is a rendering technique that creates a 3D perspective from a 2D map. Unlike full 3D rendering, raycasting is computationally efficient while still providing an immersive experience. It was popularized by games like Wolfenstein 3D in the early 1990s.

### How Raycasting Works (ELI5)

Imagine you're standing in a maze with a flashlight. You can only see what the flashlight beam hits. Now imagine you have many flashlights, and you shine each one at a slightly different angle in front of you, from left to right. Each flashlight beam will hit a wall at some distance. The closer walls will appear taller on your screen, and farther walls will appear shorter.

That's essentially what raycasting does:
1. For each vertical column of pixels on your screen, it casts a "ray" from your position
2. It calculates where that ray hits a wall
3. Based on the distance to the wall, it draws a vertical line of appropriate height
4. It applies textures to these lines to create the illusion of walls

This creates a 3D-like view from a 2D map, which is much faster than true 3D rendering.

## Project Structure

The cub3D project is organized into several modules, each handling a specific aspect of the game:

```
src/
├── core/           # Core game logic and main function
├── initialization/ # Setup and initialization
├── input/          # User input handling
├── minimap/        # Minimap rendering
├── parsing/        # Configuration file parsing
├── raycasting/     # Raycasting algorithm
├── rendering/      # Graphics rendering
└── utils/          # Utility functions
```

## Core Components

### Parsing

**Location**: `src/parsing/`

The parsing module handles reading and validating the configuration file (.cub). It ensures that all required elements are present and correctly formatted.

#### Key Files:

- **parsing.c**: Main parsing functions
  - `parse_file()`: Entry point for parsing the configuration file
  - `check_file_extension()`: Validates the file has a .cub extension

- **parsing_identifiers.c**: Handles texture and color identifiers
  - `process_texture_identifier()`: Processes NO, SO, WE, EA texture paths
  - `process_color_identifier()`: Processes F (floor) and C (ceiling) colors

- **parsing_map.c**: Handles map parsing
  - `parse_map()`: Parses the map section of the configuration file
  - `validate_map()`: Ensures the map is valid (enclosed by walls, single player)

- **parsing_textures.c**: Handles texture loading
  - `set_textures()`: Loads textures from the specified paths
  - `load_wall_textures()`: Loads the wall textures

**How It Works (ELI5)**:
The parsing module reads the configuration file line by line, like reading a recipe. First, it checks if the file has the right extension (.cub). Then it looks for specific ingredients: texture paths (NO, SO, WE, EA), colors (F, C), and the map layout. It makes sure all ingredients are present and correctly formatted. For the map, it ensures it's enclosed by walls (like making sure a puzzle has all its edge pieces) and has exactly one player starting position.

### Initialization

**Location**: `src/initialization/`

The initialization module sets up the game environment, including the window, images, and data structures.

#### Key Files:

- **init_data.c**: Initializes the game data
  - `init_data()`: Sets up the data structure with default values

- **init_window.c**: Sets up the game window
  - `init_window()`: Creates the window and initializes MLX

**How It Works (ELI5)**:
The initialization module is like setting up a board game before you start playing. It prepares the game board (window), places all the pieces in their starting positions, and makes sure everything is ready to go. It creates the window where you'll see the game, initializes the player's position and direction, and sets up the structures needed to store game information.

### Raycasting

**Location**: `src/raycasting/`

The raycasting module implements the core rendering algorithm that creates the 3D perspective.

#### Key Files:

- **raycasting.c**: Core raycasting functions
  - `render_frame()`: Main function that renders a frame
  - `get_step_for_check()`: Calculates the step direction for the DDA algorithm
  - `calc_side_dist()`: Calculates the distance to the next grid line
  - `ft_dda()`: Implements the Digital Differential Analysis algorithm
  - `ft_lineheight()`: Calculates the height of the wall on screen

- **raycasting_draw.c**: Functions for drawing walls
  - `draw_wall()`: Draws a textured wall slice
  - `draw_ceiling()`: Draws the ceiling
  - `draw_floor()`: Draws the floor

- **raycasting_textures.c**: Texture handling for walls
  - `get_texture_number()`: Determines which texture to use based on wall orientation
  - `prepare_texture_drawing()`: Sets up texture coordinates

- **raycasting_floor.c**: Floor rendering
  - `draw_floor_section()`: Draws the floor with textures

**How It Works (ELI5)**:
The raycasting module is like a painter who draws what you see in the game. For each vertical strip of your screen, it shoots an imaginary line (ray) from your position in the direction you're looking. When this line hits a wall, it measures how far away the wall is. Closer walls are drawn taller, and farther walls are drawn shorter, creating the illusion of 3D. It also figures out which part of the wall texture to use, making the walls look realistic.

### Input Handling

**Location**: `src/input/`

The input module manages user interactions, including keyboard and mouse input.

#### Key Files:

- **event_handler.c**: Main event handling
  - `handle_key_press()`: Handles key press events
  - `check_keys()`: Continuously checks for pressed keys

- **event_handler_movement.c**: Player movement
  - `move_player()`: Moves the player forward/backward
  - `strafe_player()`: Moves the player left/right
  - `rotate_player()`: Rotates the player's view

- **event_handler_position.c**: Position validation
  - `is_valid_position()`: Checks if a position is valid (not inside a wall)

- **event_handler_mouse.c**: Mouse input
  - `mouse_handler()`: Handles mouse movement for camera control

**How It Works (ELI5)**:
The input module is like the game's ears and hands. It listens for when you press keys or move the mouse, and then makes the game respond appropriately. When you press W, it moves you forward; S moves you backward; A and D move you sideways; and the arrow keys rotate your view. It also makes sure you can't walk through walls by checking if your new position would be inside a wall before moving you there.

### Rendering

**Location**: `src/rendering/`

The rendering module handles drawing graphics to the screen, including special elements like the gun.

#### Key Files:

- **gun_init.c**: Initializes the gun graphics
  - `init_gun()`: Sets up the gun image

- **gun_simple.c**: Draws the gun on screen
  - `draw_gun()`: Renders the gun at the bottom of the screen

**How It Works (ELI5)**:
The rendering module is like an artist who draws everything you see in the game. It takes care of drawing special elements like the gun at the bottom of the screen. It loads the gun image and places it in the right position, making it look like you're holding a weapon as you explore the maze.

### Minimap

**Location**: `src/minimap/`

The minimap module implements a top-down view of the map to help with navigation.

#### Key Files:

- **draw_map_2d_1.c** through **draw_map_2d_8.c**: Minimap rendering
  - `draw_map_2d()`: Main function to draw the minimap
  - `init_minimap()`: Sets up the minimap parameters
  - `draw_player_on_minimap()`: Shows the player's position on the minimap
  - `draw_map_grid()`: Draws the map grid

**How It Works (ELI5)**:
The minimap module is like having a small map in the corner of your screen. It shows a bird's-eye view of the maze, with your position marked. This helps you navigate and understand where you are in the maze. It draws walls as one color, empty spaces as another, and shows your position and direction with a different color or shape.

### Utilities

**Location**: `src/utils/`

The utilities module provides helper functions used throughout the code.

#### Key Files:

- **cleanup.c**: Memory management
  - `clean_exit()`: Frees resources and exits the program
  - `free_textures()`: Frees texture memory

- **get_next_line.c**: File reading
  - `get_next_line()`: Reads a line from a file descriptor

**How It Works (ELI5)**:
The utilities module is like a toolbox with useful tools that other parts of the game can use. It includes functions for reading files line by line (like reading a book one line at a time) and for cleaning up when the game ends (like putting away toys when you're done playing). These tools help keep the code organized and prevent memory leaks.

## How Raycasting Works

Let's dive deeper into how the raycasting algorithm works in this project:

### 1. The Camera Plane

The player has a position (x, y) and a direction they're facing (dirX, dirY). Perpendicular to this direction is the camera plane, which represents the player's field of view.

```
Player position: (posx, posy)
Direction vector: (dirx, diry)
Camera plane: (planex, planey)
```

### 2. Casting Rays

For each vertical column of the screen, a ray is cast from the player's position:

```c
// For each x (column) on the screen
for (int x = 0; x < screenWidth; x++) {
    // Calculate ray position and direction
    double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // ... DDA algorithm to find wall hit ...

    // Calculate distance to the wall
    // Draw the wall slice
}
```

### 3. Digital Differential Analysis (DDA)

The DDA algorithm efficiently finds where the ray intersects with a wall:

```c
void ft_dda(t_data *data)
{
    data->hit = false;
    while (!data->hit)
    {
        // Jump to next map square, either in x-direction, or in y-direction
        if (data->sidedistx < data->sidedisty)
        {
            data->sidedistx += data->deltadistx;
            data->mapx += data->stepx;
            data->side = false; // X-side hit
        }
        else
        {
            data->sidedisty += data->deltadisty;
            data->mapy += data->stepy;
            data->side = true; // Y-side hit
        }

        // Check if ray has hit a wall
        if (data->map[data->mapy][data->mapx] == '1')
            data->hit = true;
    }
}
```

### 4. Wall Height Calculation

Once we know where the ray hits a wall, we calculate how tall to draw the wall on screen:

```c
void ft_lineheight(t_data *data)
{
    // Calculate distance projected on camera direction
    if (data->side == false)
        data->perpwalldist = (data->sidedistx - data->deltadistx);
    else
        data->perpwalldist = (data->sidedisty - data->deltadisty);

    // Calculate height of line to draw on screen
    data->lineheight = (int)(data->window_height / data->perpwalldist);

    // Calculate lowest and highest pixel to fill in current stripe
    data->drawstart = -data->lineheight / 2 + data->window_height / 2;
    if (data->drawstart < 0)
        data->drawstart = 0;
    data->drawend = data->lineheight / 2 + data->window_height / 2;
    if (data->drawend >= data->window_height)
        data->drawend = data->window_height - 1;
}
```

### 5. Texture Mapping

We determine which texture to use based on which side of the wall was hit, and calculate the exact position in the texture:

```c
int get_texture_number(t_data *data)
{
    if (data->side)
    {
        if (data->stepy < 0)
            return (0); // North texture
        else
            return (1); // South texture
    }
    else
    {
        if (data->stepx < 0)
            return (2); // West texture
        else
            return (3); // East texture
    }
}
```

### 6. Drawing the Wall

Finally, we draw the wall slice with the appropriate texture:

```c
void draw_wall(t_data *data, int x, int y, t_tex_info *tex_info)
{
    t_wall_vars vars;

    vars.wall_pos = calc_wall_position(data, y, vars.pitch_offset);
    vars.tex_y = (int)vars.wall_pos & (TEX_HEIGHT - 1);
    vars.color = get_texture_pixel(data->tex, data->texx, vars.tex_y);

    // Draw the pixel
    mlx_put_pixel(data->img, x, y, vars.color);
}
```

## Map Format

The configuration file (.cub) follows this format:

```
NO ./path_to_north_texture.png
SO ./path_to_south_texture.png
WE ./path_to_west_texture.png
EA ./path_to_east_texture.png

F R,G,B
C R,G,B

1111111
1000001
1000001
100N001
1000001
1000001
1111111
```

- **Texture paths**: Specified with NO, SO, WE, EA identifiers
- **Colors**: Floor (F) and ceiling (C) colors in RGB format (0-255)
- **Map**: Composed of characters:
  - `1`: Wall
  - `0`: Empty space
  - `N`, `S`, `E`, `W`: Player starting position and orientation

### Validation Rules

- The file must have the `.cub` extension
- All required elements (textures, colors, map) must be present
- The map must be enclosed by walls (all `0`s must be surrounded by walls)
- Only one player position is allowed
- Texture paths must be valid and point to existing PNG files
- RGB values must be between 0 and 255

## Testing Guide

The project includes several test maps to verify different aspects of the implementation:

1. **map.cub**: The main map with a complex layout
2. **basic.cub**: A simple valid map for quick functionality testing
3. **color_parsing.cub**: Tests color parsing with different RGB values
4. **spaces.cub**: Tests handling of spaces in the map
5. **invalid_extension.txt**: Tests file extension validation
6. **missing_texture_test.cub**: Tests handling of missing textures
7. **invalid_colors.cub**: Tests validation of RGB color values
8. **unclosed_walls_test.cub**: Tests detection of unclosed walls
9. **multiple_players.cub**: Tests detection of multiple player positions
10. **missing_identifiers.cub**: Tests handling of missing required identifiers
11. **north_player.cub**: Tests north player orientation
12. **south_player.cub**: Tests south player orientation
13. **east_player.cub**: Tests east player orientation
14. **west_player.cub**: Tests west player orientation

### Running the Tests

```bash
# Compile the project
make

# Run with a valid map
./cub3d maps/map.cub

# Test invalid file extension
./cub3d maps/invalid_extension.txt

# Test missing texture
./cub3d maps/missing_texture_test.cub

# Test invalid colors
./cub3d maps/invalid_colors.cub

# Test unclosed walls
./cub3d maps/unclosed_walls_test.cub

# Test multiple players
./cub3d maps/multiple_players.cub

# Test missing identifiers
./cub3d maps/missing_identifiers.cub

# Test player orientations
./cub3d maps/north_player.cub
./cub3d maps/south_player.cub
./cub3d maps/east_player.cub
./cub3d maps/west_player.cub
```

## Common Issues

### Segmentation Fault
- Check map parsing for out-of-bounds access
- Verify texture loading is properly handled
- Ensure all pointers are initialized before use

### Black Screen
- Verify texture paths are correct
- Check that the window is properly initialized
- Ensure the player position is valid

### Performance Issues
- Large maps can cause slowdowns
- High-resolution textures may impact performance
- Complex calculations in the rendering loop can affect frame rate

### Memory Leaks
- Ensure all allocated memory is freed
- Check for proper cleanup when handling errors
- Use tools like valgrind to detect memory leaks

## Program Execution Flow

Here's a step-by-step breakdown of how the program executes, function by function:

### 1. Program Start

`main()` in `src/core/main.c`
-> Program entry point
-> ELI5: The starting line of a race

### 2. Argument Checking

`main()` in `src/core/main.c`
-> Checks if correct number of arguments (2) is provided
-> ELI5: Making sure you have your ticket before entering the theater

### 3. Data Initialization

`init_data()` in `src/initialization/init_data.c`
-> Sets up the data structure with default values
-> ELI5: Setting up your game board before playing

### 4. File Parsing

`parse_file()` in `src/parsing/parsing.c`
-> Reads and validates the .cub file
-> ELI5: Reading the recipe before cooking

  #### 4.1 File Extension Check
  `check_file_extension()` in `src/parsing/parsing_utils.c`
  -> Ensures file ends with .cub
  -> ELI5: Making sure you have the right type of book

  #### 4.2 Read File Content
  `read_file()` in `src/parsing/parsing_utils.c`
  -> Reads the file line by line
  -> ELI5: Reading each line of the recipe

  #### 4.3 Process Identifiers
  `process_identifiers()` in `src/parsing/parsing_identifiers.c`
  -> Processes texture paths and colors
  -> ELI5: Finding the ingredients in the recipe

  #### 4.4 Parse Map
  `parse_map()` in `src/parsing/parsing_map.c`
  -> Parses the map section
  -> ELI5: Understanding the map part of the instructions

  #### 4.5 Validate Map
  `validate_map()` in `src/parsing/parsing_map_validation.c`
  -> Ensures map is valid (enclosed, one player)
  -> ELI5: Making sure the puzzle has all its pieces

### 5. Window Initialization

`init_window()` in `src/initialization/init_window.c`
-> Creates the game window
-> ELI5: Opening the window to see outside

### 6. Texture Loading

`set_textures()` in `src/parsing/parsing_textures.c`
-> Loads textures from specified paths
-> ELI5: Getting the pictures ready to put on the walls

### 7. Input Hooks Setup

`mlx_key_hook()` and `mlx_loop_hook()` in `src/core/main.c`
-> Sets up keyboard and continuous input handling
-> ELI5: Setting up the buttons that control the game

### 8. Game Loop Start

`mlx_loop()` in `src/core/main.c`
-> Starts the main game loop
-> ELI5: Starting the movie

### 9. Continuous Frame Rendering

`check_keys()` in `src/input/event_handler.c`
-> Called every frame to check for key presses
-> ELI5: Constantly checking if you're pressing buttons

### 10. Player Movement

`check_basic_movement()` in `src/input/event_handler.c`
-> Handles WASD and arrow key movement
-> ELI5: Moving your character when you press buttons

  #### 10.1 Forward/Backward Movement
  `move_player()` in `src/input/event_handler_movement.c`
  -> Moves player forward/backward
  -> ELI5: Walking forward or backward

  #### 10.2 Strafing
  `strafe_player()` in `src/input/event_handler_movement.c`
  -> Moves player left/right
  -> ELI5: Stepping sideways

  #### 10.3 Rotation
  `rotate_player()` in `src/input/event_handler_movement.c`
  -> Rotates player's view
  -> ELI5: Turning your head to look around

  #### 10.4 Position Validation
  `is_valid_position()` in `src/input/event_handler_position.c`
  -> Ensures player doesn't walk through walls
  -> ELI5: Making sure you don't walk through walls

### 11. Rendering a Frame

`render_frame()` in `src/raycasting/raycasting.c`
-> Main function that renders what you see
-> ELI5: Drawing what you see on the screen

  #### 11.1 Ray Casting
  `render_frame()` in `src/raycasting/raycasting.c`
  -> Casts rays for each column of the screen
  -> ELI5: Shining flashlights to see how far away walls are

  #### 11.2 DDA Algorithm
  `ft_dda()` in `src/raycasting/raycasting.c`
  -> Finds where rays hit walls
  -> ELI5: Finding out where your flashlight beam hits a wall

  #### 11.3 Wall Height Calculation
  `ft_lineheight()` in `src/raycasting/raycasting.c`
  -> Calculates how tall to draw walls
  -> ELI5: Figuring out how tall to draw the wall based on distance

  #### 11.4 Drawing Walls
  `draw_line()` in `src/raycasting/raycasting.c`
  -> Draws a vertical wall slice
  -> ELI5: Drawing one strip of wall

  #### 11.5 Texture Mapping
  `draw_wall_section()` in `src/raycasting/raycasting_sections.c`
  -> Applies textures to walls
  -> ELI5: Putting the right picture on each part of the wall

  #### 11.6 Floor and Ceiling
  `draw_ceiling_section()` and `draw_floor_section()` in `src/raycasting/raycasting_sections.c`
  -> Draws floor and ceiling
  -> ELI5: Drawing the floor and ceiling

### 12. Minimap Rendering

`draw_map_2d()` in `src/minimap/draw_map_2d_1.c`
-> Draws the minimap
-> ELI5: Drawing a small map in the corner to help you navigate

### 13. Handling Exit

`handle_key_press()` in `src/input/event_handler.c`
-> Handles ESC key to exit
-> ELI5: Closing the game when you press Escape

`clean_exit()` in `src/utils/cleanup.c`
-> Frees resources and exits
-> ELI5: Cleaning up all the toys before going home

This flow shows how the program executes from start to finish, with each function building on the previous ones to create the complete raycasting engine.
