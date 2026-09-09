*This project has been created as part of the 42 curriculum by sabytheo and egache.*

# cub3D

## Description

**cub3D** is a first-person maze renderer written in C on top of the **MiniLibX** library, built as part of the 42 curriculum. It takes a `.cub` file describing a 2D grid and draws it as a textured 3D-looking scene the player can walk through, in the spirit of the original *Wolfenstein 3D*.

Nothing about the scene is really three-dimensional. The world is a flat character grid; the illusion comes from raycasting. For every one of the 1920 columns of the window, a ray is cast from the player's position in the direction that column represents, and walked square by square until it meets a wall. The distance to that wall decides how tall the wall slice is on screen, and the exact point where the ray landed decides which pixel column of the texture to draw. Repeat once per column, sixty times a second, and a corridor appears.

The project therefore covers three distinct problems: parsing and validating a scene description that a user wrote by hand, implementing the raycasting maths correctly enough that walls do not bend or shimmer, and doing it fast enough to stay interactive.

The repository contains two builds. The **mandatory** version renders textured walls with a flat colour for the floor and the ceiling. The **bonus** version adds a minimap, doors that open and close, an animated wall texture, textured floor and ceiling, mouse look, sprinting, and a renderer split across every core of the machine.

## Instructions

### Requirements

- `gcc` and `make`
- X11 development headers and zlib

```bash
# Debian / Ubuntu
sudo apt install gcc make xorg libxext-dev zlib1g-dev
```

MiniLibX is vendored in `mlx_linux/` and built by the Makefile — there is nothing to download.

### Compilation

```bash
git clone https://github.com/sabytheo/Cube3d.git
cd Cube3d
make          # builds cub3D
make bonus    # builds cub3D_bonus
```

| Rule | Effect |
| --- | --- |
| `make` | Builds MiniLibX, then `cub3D` |
| `make bonus` | Builds `cub3D_bonus` |
| `make run` / `make runb` | Builds and launches the corresponding binary on the sample map |
| `make valgrind` / `make valgrindb` | Same, under Valgrind |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and both binaries |
| `make re` / `make re_bonus` | Full rebuild |

Both builds use `-Wall -Wextra -Werror -g3` and link against the project's own Libft.

### Execution

Each binary takes exactly one argument, a scene file with the `.cub` extension:

```bash
./cub3D maps/map.cub
./cub3D_bonus maps/map_bonus.cub
```

Textures are referenced by relative path inside the `.cub` file, so the game is meant to be launched from the root of the repository.

## Controls

| Input | Action |
| --- | --- |
| `W` `A` `S` `D` | Move forward, left, backward, right |
| `←` `→` | Turn |
| Mouse | Look around |
| `Shift` | Sprint |
| `E` / `F` | Open / close the door in front of you *(bonus)* |
| `Esc` | Quit |

Keys can be held together — moving forward and strafing at the same time produces a real diagonal, not one axis then the other.

## Scene format

A `.cub` file holds an identifier block, then the grid. The two builds do not expect the same identifiers.

**Mandatory** — four wall textures and two colours:

```
NO ./assets/Brick_north.xpm
SO ./assets/Brick_south.xpm
WE ./assets/Brick_west.xpm
EA ./assets/Brick_east.xpm

F 104,140,104
C 1,55,156
```

**Bonus** — floor and ceiling become textures, doors get two states, and the west face is animated over six frames:

| Identifier | Meaning |
| --- | --- |
| `NO` `SO` `EA` | North, south and east wall textures |
| `WE` × 6 | The six frames of the animated west wall texture |
| `OD` / `CD` | Open and closed door textures |
| `FL` / `CE` | Floor and ceiling textures |

The grid itself uses:

| Character | Meaning |
| --- | --- |
| `0` | Walkable floor |
| `1` | Wall |
| `N` `S` `E` `W` | Player start, and the direction they face — exactly one |
| `D` | Door *(bonus)* |
| space | Void, outside the map |

Parsing rejects a file that does not end in `.cub`, is empty, misses an identifier or repeats one, contains an unknown character in the grid, has no player or several, or is not fully enclosed by walls. That last check is a flood fill from the player's position: if it escapes through a gap, the map is open and the scene is refused.

## Technical choices

**Raycasting with DDA** — rather than stepping along a ray by small increments, each ray jumps directly from one grid line to the next. The distances to the next vertical and horizontal boundary are maintained incrementally, and at every iteration the smaller one wins. It is exact, it never overshoots a thin wall, and it costs one comparison and one addition per square crossed.

**Perpendicular distance** — the distance used to size a wall slice is not the length of the ray but its projection onto the camera direction. Using the raw length would make walls bulge outward at the edges of the screen, the classic fisheye artefact. The height itself comes from the distance to the projection plane, computed once at startup from the field of view.

**Rays that do not stop at the first hit** — an open door still occupies a square in the grid, but you can see through it. So a ray keeps collecting hits until it meets something genuinely opaque — a wall or a closed door — and the slices are then drawn from the farthest to the nearest. What is behind an open doorway is drawn first, the doorway itself on top.

**One thread per core** *(bonus)* — the screen is cut into as many vertical bands as the machine has cores, reported by `sysconf(_SC_NPROCESSORS_ONLN)`, and each band is raycast by its own thread. Each thread receives its own copy of the grid and its own raycasting state, so the only thing shared between them is the image buffer, where they write to disjoint columns. The single mutable flag they share, the one that aborts every thread when one of them fails, is protected by a mutex.

**Key state, not key events** — the press and release hooks do nothing but flip booleans in a structure. All the movement is applied once per frame in the loop hook, from those booleans. This is what makes held keys, diagonals and simultaneous inputs work; reacting directly to key events would give jerky, one-direction-at-a-time movement.

**Frame-independent movement** — the time elapsed since the previous frame is measured and multiplied into every displacement, so the player's speed is the same on a fast and on a slow machine.

**Sliding collisions** — the full movement is tried first; if it is blocked, each axis is tried alone. Walking into a wall at an angle makes the player slide along it instead of sticking to it. The player is not a point either: the four corners of a small square around the new position are all tested.

**Animation by elapsed time** *(bonus)* — the animated texture advances one frame every 100 ms, measured with `gettimeofday`, not every *n* frames. The animation runs at the same speed whatever the framerate.

**Minimap on its own image** *(bonus)* — the minimap is drawn into a separate image, limited to a vision radius around the player, and composited over the main one at the end of each frame.

## Project structure

```
Cube3d/
├── Makefile
├── includes/
│   ├── cube.h, error.h              # mandatory
│   └── cube_bonus.h, error_bonus.h  # bonus
├── sources/                         # mandatory build
│   ├── main.c, init.c
│   ├── parse_map.c, parse_textures.c, parse_colors.c
│   ├── parse_grid.c, parse_grid_flood_fill.c
│   ├── load_textures.c
│   ├── bindings.c, bindings_utils.c
│   ├── raycast.c, raycast_value.c
│   ├── render.c, render_bis.c, render_utils.c
│   └── free_exit.c
├── sources_bonus/                   # bonus build: adds
│   ├── multithreading.c             # threaded renderer
│   ├── bindings_door.c              # opening and closing doors
│   ├── animation.c                  # animated texture frames
│   └── render_minimap*.c            # minimap
├── assets/                          # XPM textures
├── maps/                            # sample and edge-case scenes
├── mlx_linux/                       # vendored MiniLibX
└── Libft/
```

## Resources

### Documentation and references

- [Lode Vandevenne — Raycasting](https://lodev.org/cgtutor/raycasting.html) — the reference article on DDA raycasting, wall height and texture mapping
- [F. Permadi — Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — the geometry behind the projection plane and the fisheye correction
- [42 Docs — MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) — windows, images, hooks and the event loop
- [MiniLibX repository](https://github.com/42Paris/minilibx-linux)
- `man 7 pthreads`, `man pthread_create`, `man pthread_mutex_lock` — the threaded renderer
- `man 3 sysconf` — counting the available cores
- [XPM file format specification](https://www.xfree86.org/current/xpm.pdf) — the texture format read by `mlx_xpm_file_to_image`
- [Flood fill — Wikipedia](https://en.wikipedia.org/wiki/Flood_fill) — checking that the map is closed
- *Wolfenstein 3D* black book, Fabien Sanglard — how the original engine solved the same problems in 1992
