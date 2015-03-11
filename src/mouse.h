#ifndef MOUSE_H
#define MOUSE_H

#include "maze.h"
#include <stdlib.h>

struct _MOUSE{
	int row;
	int col;
	Direction dir; //please don't set this directly, it's gonna mess things up. use setDir
};

typedef struct _MOUSE Mouse;

Mouse *create_mouse();

/** base functions the emulate mouse movement calls */
void forward(Mouse *mouse);
void setDir(Mouse *mouse,Direction d);

char dir_to_char(Direction dir);

/** returns length 4 array of bools. must be freed */
bool *sense(Maze *maze, Mouse *mouse);

#endif