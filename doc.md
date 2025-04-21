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

## Complete File Breakdown

Here's a detailed explanation of every file in the project, what it does, and why it's needed:

### Core Module (`src/core/`)

- **main.c**: The entry point of the program
  - What it does: Initializes the program, parses arguments, sets up the game, and starts the main loop
  - Why it's needed: Every C program needs a main function to start execution
  - ELI5: The starting point of the game, like turning on a video game console

### Initialization Module (`src/initialization/`)

- **init_data.c**: Sets up the game data structure
  - What it does: Initializes all variables with default values
  - Why it's needed: Ensures all data is properly initialized before use
  - ELI5: Setting up all the game pieces before you start playing

- **init_window.c**: Creates the game window
  - What it does: Initializes the MLX window and images
  - Why it's needed: Creates the visual interface for the game
  - ELI5: Opening a window so you can see the game world

### Input Module (`src/input/`)

- **event_handler.c**: Main input handling
  - What it does: Sets up input hooks and processes input events
  - Why it's needed: Connects user input to game actions
  - ELI5: Listens for when you press buttons on your keyboard

- **event_handler_keys.c**: Keyboard input processing
  - What it does: Handles specific key presses like ESC and movement keys
  - Why it's needed: Processes keyboard commands
  - ELI5: Understands what to do when you press different keys

- **event_handler_mouse.c**: Mouse input processing
  - What it does: Handles mouse movement for camera control
  - Why it's needed: Allows looking around with the mouse
  - ELI5: Lets you look around by moving your mouse

- **event_handler_movement.c**: Player movement logic
  - What it does: Implements forward/backward movement and rotation
  - Why it's needed: Translates input into player movement
  - ELI5: Makes your character move when you press WASD or arrow keys

- **event_handler_position.c**: Position validation
  - What it does: Checks if player can move to a position
  - Why it's needed: Prevents walking through walls
  - ELI5: Makes sure you can't walk through walls

- **event_handler_position_utils.c**: Helper functions for position checking
  - What it does: Additional functions for collision detection
  - Why it's needed: Provides more detailed collision checks
  - ELI5: Extra checks to make sure you don't get stuck in walls

### Parsing Module (`src/parsing/`)

- **parsing.c**: Main parsing functions
  - What it does: Coordinates the parsing of the configuration file
  - Why it's needed: Entry point for file parsing
  - ELI5: Reads the instructions for how to set up the game

- **parsing_identifiers.c**: Processes texture and color identifiers
  - What it does: Parses NO, SO, WE, EA texture paths and F, C colors
  - Why it's needed: Extracts texture paths and colors from config
  - ELI5: Finds where the wall pictures are stored and what colors to use

- **parsing_identifiers_utils.c**: Helper functions for identifier parsing
  - What it does: Additional functions for processing identifiers
  - Why it's needed: Simplifies the main identifier parsing code
  - ELI5: Extra tools to help understand the game instructions

- **parsing_map.c**: Map parsing
  - What it does: Parses the map section of the configuration file
  - Why it's needed: Creates the game map from the config file
  - ELI5: Reads the maze layout from the instructions

- **parsing_map_utils.c**: Basic map parsing utilities
  - What it does: Helper functions for map parsing
  - Why it's needed: Simplifies the main map parsing code
  - ELI5: Tools that help understand the maze layout

- **parsing_map_utils2.c**: Additional map parsing utilities
  - What it does: More helper functions for map parsing
  - Why it's needed: Handles specific aspects of map parsing
  - ELI5: More tools to help understand the maze layout

- **parsing_map_utils3.c**: More map parsing utilities
  - What it does: Even more helper functions for map parsing
  - Why it's needed: Handles complex map parsing tasks
  - ELI5: Advanced tools for understanding complicated maze layouts

- **parsing_map_utils4.c**: Final map parsing utilities
  - What it does: Final set of helper functions for map parsing
  - Why it's needed: Completes the map parsing functionality
  - ELI5: The last set of tools needed to fully understand the maze

- **parsing_map_validation.c**: Map validation
  - What it does: Validates that the map is properly formed
  - Why it's needed: Ensures the map is playable
  - ELI5: Checks that the maze doesn't have any holes or mistakes

- **parsing_map_validation_utils.c**: Map validation helpers
  - What it does: Helper functions for map validation
  - Why it's needed: Simplifies the main validation code
  - ELI5: Extra checks to make sure the maze is built correctly

- **parsing_textures.c**: Texture loading
  - What it does: Loads textures from the specified paths
  - Why it's needed: Prepares textures for rendering
  - ELI5: Gets the wall pictures ready to be shown in the game

- **parsing_utils.c**: General parsing utilities
  - What it does: General helper functions for parsing
  - Why it's needed: Common functionality used across parsing
  - ELI5: Basic tools used throughout the instruction-reading process

### Raycasting Module (`src/raycasting/`)

- **raycasting.c**: Core raycasting algorithm
  - What it does: Implements the main raycasting logic
  - Why it's needed: Creates the 3D perspective from 2D map
  - ELI5: Figures out what walls you can see and how far away they are

- **raycasting_draw.c**: Drawing functions
  - What it does: Functions for drawing walls, floor, ceiling
  - Why it's needed: Renders the visual elements
  - ELI5: Draws what you see on the screen

- **raycasting_floor.c**: Floor rendering
  - What it does: Specialized rendering for floors
  - Why it's needed: Creates realistic floor appearance
  - ELI5: Draws the floor you're walking on

- **raycasting_floor_utils.c**: Floor rendering helpers
  - What it does: Helper functions for floor rendering
  - Why it's needed: Simplifies floor rendering code
  - ELI5: Extra tools to make the floor look good

- **raycasting_render.c**: Frame rendering
  - What it does: Coordinates the rendering of a complete frame
  - Why it's needed: Manages the overall rendering process
  - ELI5: Puts together all the parts of what you see

- **raycasting_sections.c**: Wall section rendering
  - What it does: Renders different sections of walls
  - Why it's needed: Handles the details of wall rendering
  - ELI5: Draws different parts of walls with the right pictures

- **raycasting_textures.c**: Texture application
  - What it does: Applies textures to walls
  - Why it's needed: Makes walls look realistic
  - ELI5: Puts the right pictures on each wall

- **raycasting_texture_utils.c**: Texture utilities
  - What it does: Helper functions for texture handling
  - Why it's needed: Simplifies texture application
  - ELI5: Tools that help put pictures on walls correctly

- **raycasting_utils.c**: General raycasting utilities
  - What it does: Helper functions for raycasting
  - Why it's needed: Common functionality for raycasting
  - ELI5: Basic tools used throughout the wall-finding process

### Rendering Module (`src/rendering/`)

- **gun_init.c**: Gun initialization
  - What it does: Sets up the gun graphics
  - Why it's needed: Prepares the gun for display
  - ELI5: Gets the gun picture ready to show

- **gun_simple.c**: Gun rendering
  - What it does: Draws the gun on screen
  - Why it's needed: Shows the gun in the game
  - ELI5: Draws the gun at the bottom of your screen

- **gun_utils.c**: Gun utilities
  - What it does: Helper functions for gun rendering
  - Why it's needed: Simplifies gun rendering code
  - ELI5: Extra tools to make the gun look good

### Minimap Module (`src/minimap/`)

- **draw_map_2d_1.c**: Main minimap functions
  - What it does: Core functions for minimap rendering
  - Why it's needed: Initializes and coordinates minimap drawing
  - ELI5: Starts drawing the small map in the corner

- **draw_map_2d_2.c** through **draw_map_2d_8.c**: Additional minimap functions
  - What it does: Various aspects of minimap rendering
  - Why it's needed: Completes the minimap functionality
  - ELI5: Draws different parts of the small map (walls, player, etc.)

### Utilities Module (`src/utils/`)

- **cleanup.c**: Resource cleanup
  - What it does: Frees allocated memory and resources
  - Why it's needed: Prevents memory leaks
  - ELI5: Cleans up all the toys when you're done playing

- **cleanup_utils.c**: Cleanup helpers
  - What it does: Helper functions for cleanup
  - Why it's needed: Simplifies cleanup code
  - ELI5: Extra tools to make sure everything is cleaned up properly

- **get_next_line.c**: Line reading
  - What it does: Reads a line from a file descriptor
  - Why it's needed: Used for reading configuration files
  - ELI5: Reads one line at a time from the instruction book

- **get_next_line_utils.c** and **get_next_line_utils2.c**: Line reading helpers
  - What it does: Helper functions for line reading
  - Why it's needed: Simplifies line reading code
  - ELI5: Extra tools to help read the instruction book

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
