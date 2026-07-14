*This project has been created as part of the 42 curriculum by davdiaz-, pestelle.*

# cub3D

`cub3D` is a small first-person 3D maze renderer written in C with MiniLibX. It reads a scene from a `.cub` file, validates the configuration and map, converts the parsed data into a rendering scene, and uses raycasting with the Digital Differential Analyzer (DDA) algorithm to draw textured walls in real time.

This document is both a project overview and a practical guide for development, testing, debugging, and peer evaluation.

## Table of contents

- [Description](#description)
- [Features](#features)
- [How the program works](#how-the-program-works)
- [Architecture](#architecture)
- [The `.cub` scene format](#the-cub-scene-format)
- [Parser and validation pipeline](#parser-and-validation-pipeline)
- [Raycasting guide](#raycasting-guide)
- [Movement and collision](#movement-and-collision)
- [Instructions](#instructions)
- [Controls](#controls)
- [Makefile targets](#makefile-targets)
- [Error handling and memory ownership](#error-handling-and-memory-ownership)
- [Testing guide](#testing-guide)
- [Troubleshooting](#troubleshooting)
- [Project structure](#project-structure)
- [Development workflow](#development-workflow)
- [Pre-evaluation checklist](#pre-evaluation-checklist)
- [Resources](#resources)
- [Authors and responsibilities](#authors-and-responsibilities)

## Description

The goal of cub3D is to create a realistic first-person representation of the inside of a maze. The project introduces the fundamentals behind early 3D games: a two-dimensional grid is transformed into a three-dimensional view by casting one ray for every vertical screen column.

The project is divided into three main layers:

1. **Parsing and validation** reads the `.cub` file and rejects malformed configurations or open maps.
2. **The bridge** converts parser-owned structures into the compact scene structure expected by the graphics engine.
3. **The graphics engine** initializes MiniLibX, loads textures, handles input, casts rays, draws frames, and releases graphical resources.

The mandatory implementation supports four directional wall textures, independent floor and ceiling colors, keyboard movement, rotation, collision detection, and clean window closing.

## Features

- Scene loading from a `.cub` file.
- Four XPM wall textures: north, south, west, and east.
- Independent RGB floor and ceiling colors.
- Validation of required identifiers and duplicate configuration entries.
- Validation of texture extensions and file accessibility.
- Validation of map characters, boundaries, spaces, and player spawn.
- Support for non-rectangular map rows through per-row lengths.
- DDA raycasting, one ray per screen column.
- Perspective-correct wall height based on perpendicular distance.
- Direction-dependent texture selection and texture coordinate mapping.
- Continuous movement and rotation through key press/release state.
- Axis-separated collision detection, allowing the player to slide along walls.
- Clean MiniLibX image, texture, window, display, and engine destruction.

No bonus features are currently documented as part of the implemented scope.

## How the program works

The high-level execution flow is:

```text
main
 ├─ initialize t_game
 ├─ validate command-line arguments
 ├─ open and parse the .cub file
 │   ├─ read NO/SO/WE/EA texture paths
 │   ├─ read F/C colors
 │   ├─ read map rows
 │   ├─ validate map boundaries and spaces
 │   └─ locate player position and direction
 ├─ build t_cub3d_scene from parser data
 ├─ initialize MiniLibX and graphical resources
 ├─ enter the event/render loop
 │   ├─ process held keys
 │   ├─ update player position and direction
 │   ├─ cast one ray per screen column
 │   └─ draw the completed framebuffer
 └─ destroy resources and exit
```

The parser and renderer deliberately use separate structures. `t_game` owns the raw parsed configuration, while `t_cub3d_scene` is the interface passed to the graphics engine. `src/bridge.c` is the only conversion layer between them.

## Architecture

### Core parser structures

- `t_game`: top-level parser state, file descriptor, map, player, and configuration.
- `t_config`: the four texture paths plus floor and ceiling colors.
- `t_map`: map grid, dimensions, and metadata for every row.
- `t_line_data`: trimmed row boundaries, row type, and original row index.
- `t_player`: parsed position, direction vector, camera plane, and spawn letter.

### Graphics structures

- `t_cub3d_scene`: parser-to-engine contract containing borrowed map and texture pointers, colors, spawn data, dimensions, and row lengths.
- `t_cub3d_engine`: MiniLibX context, window, framebuffer, loaded textures, scene, player state, and input state.
- `t_cub3d_img`: MiniLibX image pointer and pixel-buffer metadata.
- `t_cub3d_ray`: all temporary values used to cast and draw one screen column.

### Important ownership rule

The scene mostly **borrows** data from `t_game`; it does not duplicate the map or texture strings. The row-length array created by `build_scene()` is the exception and must be freed separately. The graphics engine owns only its MiniLibX resources and its own engine allocation.

This distinction prevents accidental double frees and makes cleanup responsibilities explicit.

## The `.cub` scene format

The program accepts exactly one argument with the `.cub` extension:

```sh
./cub3d path/to/scene.cub
```

A scene contains six configuration elements followed by the map. Configuration elements may appear in any order and may be separated by empty lines. The map must always be the final section.

### Required identifiers

| Identifier | Meaning | Example |
|---|---|---|
| `NO` | North-facing wall texture | `NO textures/north.xpm` |
| `SO` | South-facing wall texture | `SO textures/south.xpm` |
| `WE` | West-facing wall texture | `WE textures/west.xpm` |
| `EA` | East-facing wall texture | `EA textures/east.xpm` |
| `F` | Floor RGB color | `F 50,50,50` |
| `C` | Ceiling RGB color | `C 120,180,255` |

Texture files must use the `.xpm` extension, must exist, and must be readable from the process working directory.

### Map characters

| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Walkable floor |
| `N` | Player facing north |
| `S` | Player facing south |
| `E` | Player facing east |
| `W` | Player facing west |
| Space | Significant map padding or an exterior void |

The map must contain exactly one player spawn and must be completely surrounded by walls. Spaces are preserved and validated; they are not automatically converted into walls or floor.

### Minimal example

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm
F 50,50,50
C 120,180,255

111111
100001
10N001
100001
111111
```

Paths are resolved relative to the directory from which the executable is launched, not relative to the `.cub` file itself.

> **Repository note:** `hell.cub` currently contains placeholder `.png` paths. The parser and MiniLibX loader expect valid `.xpm` files, so update those paths or use another valid scene before running it.

## Parser and validation pipeline

### 1. Argument validation

`main.c` requires exactly one scene argument and checks that its name ends in `.cub`.

### 2. Configuration discovery

`figure_sections()` reads lines until all four texture identifiers and both color identifiers have been found. Two flag arrays track missing and duplicate entries:

```text
textures: NO SO WE EA
colors:   F  C
```

An identifier appearing twice is rejected. Empty lines between configuration entries are ignored.

### 3. Texture path parsing

`parse_paths()`:

1. Confirms that the line contains an identifier and one path.
2. Confirms that the identifier matches the expected slot.
3. Trims surrounding whitespace.
4. Requires a `.xpm` suffix.
5. Opens the file to confirm that it exists and is readable.
6. Duplicates the path into `t_config`.

### 4. Color parsing

`parse_colors()` processes three comma-separated decimal components. It verifies the syntax, splits the components, removes allowed spaces, converts them to integers, and checks that every value is in `[0, 255]`.

The subject's canonical form is `F 220,100,0`. The current implementation also applies a whitespace-based word count that expects input shaped like `F 220, 100, 0`. This restriction should be removed before evaluation so both the canonical no-space form and allowed whitespace variants are accepted.

The final packed color is stored as:

```c
(red << 16) | (green << 8) | blue
```

### 5. Map extraction

`parse_map()` reads the remaining lines without flattening the map into a rectangle. It stores every row independently, preserving meaningful spaces and irregular row lengths.

The first validation pass classifies rows and checks:

- allowed map characters;
- wall boundaries at the meaningful start and end of a row;
- the number of player spawn characters;
- top, middle, and bottom row structure;
- map width and height.

### 6. Directional space validation

The `system_search_engine` performs a second pass over spaces and tabs. For each whitespace position, it determines whether the space is inside the meaningful row bounds or outside on the left/right, then searches toward the nearest meaningful cell in four directions.

The search rejects a whitespace path that exposes walkable floor or a player spawn to an exterior void. This is the project-specific mechanism for validating non-rectangular maps with indentation and internal spacing.

### 7. Player extraction

`fill_out_player()` scans the validated map, places the player at the center of the spawn cell (`column + 0.5`, `row + 0.5`), builds the initial direction vector, and computes a perpendicular camera plane with length `0.66`.

### 8. Parser-to-engine bridge

`build_scene()` copies scalar scene information and pointer references into `t_cub3d_scene`. It also builds `row_lengths`, allowing rendering and collision code to safely query irregular rows without reading past a string boundary.

## Raycasting guide

The renderer generates a frame one vertical screen column at a time.

### 1. Camera-space coordinate

For screen column `x`, the code maps the column to the interval `[-1, 1]`:

```c
camera_x = 2.0 * x / screen_width - 1.0;
```

`-1` is the left side of the camera plane, `0` is the center, and `1` is the right side.

### 2. Ray direction

The ray direction combines the player direction and camera plane:

```c
ray_dir = player_dir + camera_plane * camera_x;
```

This produces one ray for each visible horizontal angle.

### 3. DDA preparation

The ray starts in the player's current grid cell. `delta_dist_x` and `delta_dist_y` represent how far the ray must travel to cross one complete grid cell on each axis. `step_x` and `step_y` indicate whether the ray advances in the positive or negative direction.

### 4. DDA traversal

DDA repeatedly advances through whichever next grid boundary is closer:

```text
if next X boundary is closer:
    move one cell on X
else:
    move one cell on Y
```

Traversal ends when the current map cell is a wall (`1`). Out-of-range cells and void spaces are treated defensively as walls by the graphics layer.

### 5. Perpendicular distance and projection

The engine uses perpendicular wall distance rather than the raw ray length. This avoids the fish-eye distortion that would otherwise curve flat walls.

Projected wall height is:

```c
line_height = screen_height / perpendicular_distance;
```

The slice is vertically centered and clipped to the framebuffer.

### 6. Texture selection

The hit axis and ray direction determine which texture is used. The exact wall hit coordinate is converted into an X coordinate inside the chosen texture. The coordinate is mirrored for specific directions so textures are not displayed backwards.

### 7. Texture sampling

The projected slice is traversed from top to bottom. Each screen pixel maps to a texture Y coordinate, and the sampled texture pixel is written into the framebuffer.

### 8. Frame presentation

The framebuffer is first cleared with ceiling and floor colors. After all wall columns have been drawn, the completed image is sent to the window with a single MiniLibX image operation.

## Movement and collision

Movement is state-based: key press events enable an input flag and key release events disable it. The loop hook applies all active inputs every frame.

- Forward/backward movement follows the direction vector.
- Strafing uses the perpendicular direction.
- Rotation applies a 2D rotation matrix to both the direction vector and camera plane.
- Collision checks X and Y independently, which allows smooth sliding along a wall instead of stopping both axes at once.

The current constants are defined in `src/engine/cub3d_private.h`:

```c
CUB3D_MOVE_SPEED
CUB3D_ROT_SPEED
CUB3D_PLANE_LEN
```

Changing these values affects movement speed, rotation speed, and field of view.

## Instructions

### Requirements

- A C compiler (`cc` or GCC/Clang).
- GNU Make.
- MiniLibX sources in `minilibx-linux/`.
- The included Libft sources in `lib/libft_plus/`.
- X11 development libraries on Linux.

On Debian/Ubuntu Linux or WSL2:

```sh
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev zlib1g-dev
```

On WSL, graphical execution also requires WSLg or another working X server.

### Repository layout required before compilation

```text
Cub3d-prueba/
├── Makefile
├── includes/
├── lib/libft_plus/
├── minilibx-linux/
└── src/
```

If `minilibx-linux/` is missing, the build stops at the `mlx` target.

### Compilation

```sh
make
```

For a completely clean rebuild:

```sh
make re
```

The current Makefile creates an executable named `cub3d`:

```sh
./cub3d path/to/scene.cub
```

The 42 subject names the program `cub3D`. Before submission, ensure the executable name and evaluation command match the exact subject requirement.

## Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| Left arrow | Rotate left |
| Right arrow | Rotate right |
| `Esc` | Close the window and stop the loop |
| Window close button | Close the window and stop the loop |

## Makefile targets

| Target | Purpose |
|---|---|
| `make` / `make all` | Build Libft, MiniLibX, objects, and the executable |
| `make clean` | Remove project and MiniLibX object files |
| `make fclean` | Run `clean`, remove the executable, and clean Libft |
| `make re` | Completely rebuild the project |
| `make mlx` | Build MiniLibX only |

The subject lists a `bonus` target. Add a harmless or functional `bonus` rule before evaluation if the evaluator requires the target, even when no bonus feature is submitted.

## Error handling and memory ownership

Parser errors are printed through `print_error()`. Fatal parser paths call `exit_error()`, which closes the open scene descriptor and releases parser-owned map and configuration allocations.

The graphics engine reports initialization, validation, and texture failures through its engine error helper, returns a failure status, and releases partially created MiniLibX resources through `cub3d_engine_destroy()`.

### Ownership summary

| Resource | Owner | Cleanup responsibility |
|---|---|---|
| Map rows and map pointer array | `t_game` | parser/game cleanup |
| Row metadata (`map.lines`) | `t_game` | parser/game cleanup |
| Texture path strings | `t_game.config` | parser/game cleanup |
| `scene.row_lengths` | bridge/caller | free after engine finishes |
| MiniLibX context and display | graphics engine | `cub3d_engine_destroy()` |
| Window | graphics engine | `mlx_destroy_window()` |
| Framebuffer and texture images | graphics engine | `mlx_destroy_image()` |

When adding an error path, release only resources already created at that point. Avoid freeing scene map or texture pointers from the graphics engine because they are borrowed from `t_game`.

## Testing guide

### Compilation checks

```sh
make fclean
make
make
```

The first `make` must compile successfully with `-Wall -Wextra -Werror`. The second must not relink unnecessarily.

### Norm check

```sh
norminette includes src lib/libft_plus
```

Fix every reported error before evaluation, including errors in bonus files if bonuses are submitted.

### Parser test matrix

Create separate `.cub` files for each case:

- valid minimal map;
- configuration entries in a different order;
- blank lines between configuration entries;
- missing texture identifier;
- duplicated identifier;
- wrong texture extension;
- missing or unreadable texture file;
- missing floor or ceiling color;
- RGB values below `0` or above `255`;
- missing commas or extra components;
- invalid map character;
- no player;
- more than one player;
- open map on each side;
- non-rectangular map with valid spaces;
- non-rectangular map with a hidden leak through spaces;
- empty file;
- wrong argument count;
- argument without the `.cub` extension.

Every invalid case must exit cleanly and print `Error\n` followed by an explicit message.

### Runtime test matrix

- Walk forward and backward until reaching every wall orientation.
- Strafe against walls and corners.
- Hold movement and rotation keys simultaneously.
- Verify that each wall direction displays the expected texture.
- Confirm floor and ceiling colors.
- Press `Esc` repeatedly.
- Close with the window's red cross.
- Minimize, restore, and change focus to test smooth window management.

### Memory testing

Run Valgrind on both valid and invalid inputs:

```sh
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  ./cub3d path/to/scene.cub
```

Close the game normally with `Esc` or the window close button. Killing it with `Ctrl+C` or `timeout` bypasses normal cleanup and can produce misleading leak reports.

MiniLibX/X11 may produce third-party warnings. Investigate every record originating from project source files and ensure there are no definitely or indirectly lost blocks owned by this project.

### Useful debugging build

The Makefile already enables debug symbols with `-g`. To investigate a crash:

```sh
gdb --args ./cub3d path/to/scene.cub
```

Inside GDB:

```text
run
bt
```

## Troubleshooting

### `make: minilibx-linux: No such file or directory`

Place the Linux MiniLibX sources at `./minilibx-linux`, matching `MLX_DIR` in the Makefile.

### Undefined Libft references during linking

Do not reuse a `.a` archive compiled on another operating system. Rebuild Libft locally:

```sh
make -C lib/libft_plus fclean
make -C lib/libft_plus
make
```

### `Wrong path`

Confirm that every texture path:

- ends in `.xpm`;
- contains no unintended extra word;
- points to an existing readable file;
- is correct relative to the current working directory.

### `could not load XPM texture`

A file may exist and still not be a valid XPM image. Check its real format and ensure MiniLibX can parse it.

### `Error: Can't open display` or no window appears

Confirm that an X11 display is available. Under WSL, use WSLg or configure an external X server and the `DISPLAY` variable.

### Header type or circular-include errors

Keep the public headers one-directional. `cub3d.h` may include parser and engine headers, but low-level engine/structure headers should not include `cub3d.h` back. Use forward declarations such as `struct s_game *` when only a pointer is required.

### The map parses but the renderer fails

Check that the player spawn is not inside a wall, all four scene texture pointers are present, row lengths match the original strings, and the image files are valid XPMs.

## Project structure

```text
.
├── Makefile
├── README.md
├── en.subject.pdf
├── hell.cub
├── includes/
│   ├── cub3d.h                 # Main parser/public declarations
│   ├── cub3d_engine.h          # Scene and engine public API
│   └── cub3d_structs.h         # Parser/game structures
├── lib/
│   └── libft_plus/             # Libft and its Makefile
├── minilibx-linux/             # MiniLibX source dependency
└── src/
    ├── main.c                  # Entry point and top-level flow
    ├── init_data.c             # Zero-initializes t_game
    ├── exit_error.c            # Parser error reporting and cleanup
    ├── bridge.c                # t_game -> t_cub3d_scene conversion
    ├── parsing/                # Configuration and map parsing
    ├── system_search_engine/   # Directional validation of spaces
    └── engine/                 # MiniLibX, input, raycasting, rendering
```

### Engine file guide

| File | Responsibility |
|---|---|
| `cub3d_init.c` | Allocate engine, apply defaults, create window/frame |
| `cub3d_scene.c` | Validate scene, player, map, and texture pointers |
| `cub3d_texture.c` | Load and destroy XPM textures |
| `cub3d_image.c` | Framebuffer/image creation and pixel access |
| `cub3d_input.c` | Key events and window close event |
| `cub3d_player.c` | Movement, collision, and rotation |
| `cub3d_ray_init.c` | Initialize one ray and DDA distances |
| `cub3d_ray_hit.c` | DDA traversal and wall-slice projection |
| `cub3d_ray_texture.c` | Select orientation texture and texture X |
| `cub3d_ray_draw.c` | Sample and draw a textured vertical slice |
| `cub3d_raycast.c` | Coordinate the ray pipeline for one column |
| `cub3d_render.c` | Clear, render, display, and run the loop |
| `cub3d_cleanup.c` | Destroy all engine-owned resources |

## Development workflow

The original team workflow is:

1. Work on a dedicated branch; do not push directly to `main`.
2. Open or review changes together before merging.
3. Keep functions small, Norm-compliant, and documented where the logic is not obvious.
4. Rebase or merge carefully when parser and engine interfaces change.
5. Run compilation, parser tests, graphical tests, and Valgrind before merging.

When changing a shared structure such as `t_game` or `t_cub3d_scene`, update all of the following together:

- its defining header;
- initialization code;
- the bridge;
- cleanup ownership;
- parser or engine consumers;
- relevant README sections and tests.

## Pre-evaluation checklist

- [ ] `README.md` is at the repository root and its first line matches the subject.
- [ ] The executable name exactly matches the subject (`cub3D`, including case).
- [ ] `CC`, flags, and every required Makefile rule comply with the subject.
- [ ] A `bonus` rule exists if required by the evaluator.
- [ ] A second `make` performs no unnecessary relinking.
- [ ] `norminette` reports no errors.
- [ ] MiniLibX and Libft sources are present in the expected locations.
- [ ] Valid XPM textures and at least one valid `.cub` scene are included.
- [ ] Every required identifier works in any allowed order.
- [ ] RGB parsing accepts the canonical subject form (`F 220,100,0`) and allowed whitespace variants.
- [ ] Invalid scenes always print `Error\n` plus an explicit message.
- [ ] The map accepts valid spaces and rejects every open boundary.
- [ ] Exactly one player spawn is required.
- [ ] All four wall orientations use the correct textures.
- [ ] `W`, `A`, `S`, `D`, arrow keys, `Esc`, and the window close button work.
- [ ] The window remains responsive when minimized or unfocused.
- [ ] Valgrind reports no project-owned leaks on success or error paths.
- [ ] Both authors can explain the parser, bridge, DDA, texture mapping, collision, and cleanup flow.

## Resources

### Classic references

- [Project subject](en.subject.pdf) — mandatory requirements and evaluation scope.
- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html) — step-by-step explanation of camera rays, DDA, projection, and textured walls.
- [MiniLibX Linux source](https://github.com/42Paris/minilibx-linux) — library source and Linux build information.
- [Digital Differential Analyzer on Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) — general background on DDA traversal.
- [X PixMap format](https://en.wikipedia.org/wiki/X_PixMap) — overview of the XPM image format used for textures.
- Manual pages: `man 2 open`, `man 2 read`, `man 3 malloc`, `man 3 free`, `man 3 sin`, and `man 3 cos`.

### Use of AI

AI tools were used as an assistant for repetitive and review-oriented tasks:

- comparing the repository structure with the subject's README requirements;
- helping identify compilation issues such as incompatible declarations and circular header dependencies;
- suggesting parser, runtime, and Valgrind test cases;
- organizing and drafting this documentation;
- checking that the written explanation follows the real parser-to-renderer flow.

All suggestions were reviewed against the source code and tested where applicable. The authors remain responsible for understanding, validating, and defending every part of the project. AI output was not treated as authoritative and should be reviewed with peers before submission.

## Authors and responsibilities

- **davdiaz-** — project infrastructure, `.cub` parser, color/path parsing, map extraction, directional map validation, error cleanup, and integration data.
- **pestelle** — graphics architecture, raycasting mathematics, DDA traversal, texture projection, framebuffer rendering, input, movement, collision, and MiniLibX lifecycle.

Both authors share responsibility for integration, testing, memory safety, documentation, and final evaluation readiness.
