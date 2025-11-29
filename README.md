# cub3D

A 3D maze game inspired by Wolfenstein 3D, built using raycasting techniques with the MLX42 graphics library. This project recreates the classic first-person perspective experience where players navigate through a maze rendered in real-time 3D.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Map Configuration](#map-configuration)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Credits](#credits)

---

## About

**cub3D** is a 42 school project that implements a raycasting engine similar to the classic Wolfenstein 3D. The project demonstrates fundamental concepts in computer graphics, including:

- Raycasting algorithm for 3D rendering
- Texture mapping
- Player movement and collision detection
- Parsing and validation of map files
- Real-time rendering with MLX42

---

## Features

- ✅ **Real-time 3D rendering** using raycasting
- ✅ **Textured walls** with support for different textures per direction (North, South, East, West)
- ✅ **Smooth player movement** (forward, backward, strafe left/right)
- ✅ **Camera rotation** (turn left/right)
- ✅ **Minimap** for navigation assistance
- ✅ **Custom map support** via `.cub` configuration files
- ✅ **Collision detection** to prevent walking through walls
- ✅ **Configurable floor and ceiling colors**

---

## Requirements

### System Requirements

- macOS (tested on macOS with Homebrew)
- CMake 3.18+
- GLFW library
- OpenGL support

### Dependencies

- **MLX42**: Graphics library (included in `libs/MLX42/`)
- **libft**: Custom C library (included in `libs/Libft/`)
- **get_next_line**: Line reading utility (included in `libs/get_next_line/`)

---

## Installation

1. **Clone the repository:**

```bash
git clone https://github.com/Yoneva/cub3D.git
cd cub3D
```

2. **Install GLFW (if not already installed):**

```bash
brew install glfw
```

3. **Build the project:**

```bash
cd srcs
make
```

This will:
- Compile the libft library
- Build MLX42 using CMake
- Compile the main cub3D executable

---

## Usage

Run the program with a map file:

```bash
./cub3d maps/cube.cub
```

or

```bash
./cub3d maps/simple.cub
```

### Command Line Arguments

```
./cub3d <map_file.cub>
```

- `<map_file.cub>`: Path to a valid `.cub` map configuration file

---

## Map Configuration

Map files use the `.cub` extension and follow a specific format:

### Format Example

```
NO /path/to/north_texture.png
SO /path/to/south_texture.png
WE /path/to/west_texture.png
EA /path/to/east_texture.png

F 220,100,0
C 225,30,0

11111111
10000001
100N0001
10000001
10000001
11111111
```

### Configuration Elements

#### Texture Paths
- `NO`: North wall texture (PNG format)
- `SO`: South wall texture (PNG format)
- `WE`: West wall texture (PNG format)
- `EA`: East wall texture (PNG format)

#### Colors
- `F`: Floor color in RGB format (e.g., `220,100,0`)
- `C`: Ceiling color in RGB format (e.g., `225,30,0`)

#### Map Layout
- `1`: Wall
- `0`: Empty space (walkable)
- `N`, `S`, `E`, `W`: Player starting position and orientation
  - `N`: Facing North
  - `S`: Facing South
  - `E`: Facing East
  - `W`: Facing West
- ` ` (space): Void (treated as wall for collision)

### Map Rules

1. The map must be surrounded by walls (`1`)
2. There must be exactly **one** player spawn point
3. Maps must be rectangular (normalized internally with spaces)
4. Maximum map size: 40 columns × 22 rows (for performance)
5. Empty lines before the map are skipped

---

## Controls

### Movement
| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` / `Q` | Strafe left |
| `D` | Strafe right |

### Camera
| Key | Action |
|-----|--------|
| `←` (Left Arrow) | Turn left |
| `→` (Right Arrow) | Turn right |

### System
| Key | Action |
|-----|--------|
| `ESC` | Exit game |

---

## Project Structure

```
cub3D/
├── includes/
│   ├── raycasting.h       # Raycasting engine structures and functions
│   ├── parsing.h          # Map and config parsing structures
│   └── texture.h          # Texture management functions
├── libs/
│   ├── Libft/             # Custom C library
│   ├── get_next_line/     # GNL for file reading
│   └── MLX42/             # Graphics library
├── srcs/
│   ├── main.c             # Entry point
│   ├── parsing/           # Map and config parsing
│   │   ├── parsing.c
│   │   ├── parse_map.c
│   │   ├── parse_texture.c
│   │   └── Utils/
│   ├── raycasting/        # Core rendering engine
│   │   ├── raycasting.c
│   │   ├── cast_ray.c
│   │   ├── draw_frame.c
│   │   ├── intersections.c
│   │   ├── player_pos.c
│   │   ├── keys_event.c
│   │   ├── mini_map.c
│   │   └── utils.c
│   ├── texturing/         # Texture loading and mapping
│   │   ├── textures.c
│   │   └── helper.c
│   └── maps/              # Example map files
└── textures/              # Texture image files (.png)
```

---

## Technical Details

### Raycasting Algorithm

The rendering engine uses a **Digital Differential Analysis (DDA)** raycasting approach:

1. **Ray Generation**: For each screen column, cast a ray from the player's position
2. **Grid Traversal**: Step through the grid checking for wall intersections
   - Horizontal intersections (checking horizontal grid lines)
   - Vertical intersections (checking vertical grid lines)
3. **Distance Calculation**: Compute the distance to the nearest wall hit
4. **Fish-eye Correction**: Apply `cos(angle_difference)` to prevent distortion
5. **Wall Projection**: Calculate wall height based on corrected distance
6. **Texture Mapping**: Map texture coordinates to the wall strip

### Key Formulas

#### Normalize Angle (0 to 2π)
```c
angle = fmod(angle, 2π)
if (angle < 0) angle += 2π
```

#### Euclidean Distance
```c
distance = sqrt((x2 - x1)² + (y2 - y1)²)
```

#### Fish-eye Correction
```c
corrected_distance = ray_distance * cos(ray_angle - player_angle)
```

#### Wall Height Projection
```c
wall_height = (TILE_SIZE / corrected_distance) * distance_to_projection_plane
```

#### Texture Coordinate Mapping
```c
wall_x = hit_position - floor(hit_position)  // 0.0 to 1.0
tex_x = wall_x * texture_width
tex_y = (pixel_y - screen_center + wall_height/2) * texture_height / wall_height
```

### Performance Optimizations

- Pre-normalized map to rectangular grid
- Efficient grid stepping with DDA
- Minimal trigonometric calculations per frame
- Direct pixel manipulation for rendering

---

## Compilation Flags

The project compiles with:
- `-Wall -Wextra -Werror`: Strict warning and error checking
- `-I` flags for header includes
- `-L` flags for library paths
- Frameworks: `-framework Cocoa -framework OpenGL -framework IOKit`

---

## Makefile Targets

```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild from scratch
```

---

## Known Limitations

- Only PNG textures are supported (not XPM)
- Map size limited to 40×22 for optimal performance
- No support for sprites or enemies
- No support for doors or interactive elements
- Ceiling and floor are solid colors (no textures)

---

## Credits

**Authors**: 
- amsbai
- hasbayou

**Libraries**:
- [MLX42](https://github.com/codam-coding-college/MLX42) - Graphics library
- GLFW - Window and input handling
- Math library - Trigonometric functions

**Inspiration**:
- Wolfenstein 3D (id Software, 1992)
- Lode's Raycasting Tutorial

---

## License

This project is part of the 42 school curriculum. Feel free to use it for educational purposes.

---

## Troubleshooting

### Textures not loading
- Ensure texture paths in `.cub` file are absolute or relative to execution directory
- Verify PNG files exist at specified paths
- Check file permissions

### Compilation errors
- Ensure GLFW is installed: `brew install glfw`
- Check that MLX42 submodule is initialized
- Verify CMake version is 3.18 or higher

### Game crashes on startup
- Validate map file format (walls around edges, single player spawn)
- Check map size doesn't exceed 40×22
- Ensure RGB values are in range 0-255

**Have fun exploring the maze! 🎮**
