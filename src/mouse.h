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

/** creates a mouse */
Mouse *create_mouse();

/** takse the given character and moves in that direction **/
void execute_command(Mouse *mouse, char dir_char);

/** base functions the emulate mouse movement calls*/
void forward(Mouse *mouse);

/**update row and col numbers given based on dir*/
void update_pos(Direction dir, int *row, int *col);

/** literally just sets mouse position. pretty useless, but eventually will cause physical mouse to turn */
void turn_to_face(Mouse *mouse,Direction d);

/** translate a Dir (integer 0=N 1=E 2=S 3=W) into the character representation*/
char dir_to_char(Direction dir);

/** the obvious opposite of dir to char **/
Direction char_to_dir(char c); 

/** returns length 4 array of bools. must be freed */
bool *sense(Maze *maze, Mouse *mouse);

#endif