# Cub3D

A 3D game based on raycasting, inspired by Wolfenstein 3D.

## Description

Cub3D is a 42 school project that aims to recreate a simple 3D game environment using the principles of raycasting. This technique simulates a 3D perspective from a 2D map.

## Features

- First-person perspective navigation
- Textured walls with different appearance based on orientation
- Minimap for navigation aid
- Collision detection with walls
- Movement using WASD keys and rotation using arrow keys

## Installation

### Prerequisites

- GCC compiler
- Make
- CMake (for MLX42 library)
- GLFW (for MLX42 library)

### Installing dependencies on Linux

```bash
sudo apt-get update
sudo apt-get install cmake make gcc libglfw3 libglfw3-dev
```

### Building the project

Clone the repository and compile the project:

```bash
git clone <repository-url>
cd cub3d
make
```

## Usage

### Running the game

```bash
./cub3d maps/map.cub
```

### Controls

- W: Move forward
- S: Move backward
- A: Strafe left
- D: Strafe right
- Left Arrow: Rotate camera left
- Right Arrow: Rotate camera right
- ESC: Exit the game

### Map format

The game reads map files with a `.cub` extension. Map files should follow this format:

```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png

F R,G,B
C R,G,B

111111111111
100000000001
100000000001
100000000001
100000N00001
111111111111
```

- `NO`, `SO`, `WE`, `EA`: Paths to wall textures for each orientation
- `F`: Floor color in RGB format (0-255)
- `C`: Ceiling color in RGB format (0-255)
- Map characters:
  - `1`: Wall
  - `0`: Empty space
  - `N`, `S`, `E`, `W`: Starting position and orientation of the player

The map must be closed/surrounded by walls, and there must be exactly one player position.

## Author

Created by [Rick] 