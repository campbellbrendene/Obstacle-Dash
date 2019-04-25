# Obstacle Dash
A simple text-based game written in C++.

This really is just a project for improving my (very poor) C++ skills and for learning new things. The game itself actually turned out to be quite fun.

## Gameplay
<!-- TODO: Insert image/gif of gameplay -->
Using the LEFT and RIGHT arrow keys, the player dodges incoming obstacles. The player has three lives, and loses one every time they get hit by an obstacle.

### Controls
 - `LEFT arrow`: Move left
 - `RIGHT arrow`: Move right
 - `SPACE`: Pause/resume

## Compiling
This program is designed to run on Linux, and will likely not work on Windows due to libraries missing (I have not tried it--if you get it working on Windows please let me know).

To compile, just use make:
```
$ make -B -j4
```

You may need to install ncurses via your package manager. With apt:
```
# apt install libncurses5-dev
```
