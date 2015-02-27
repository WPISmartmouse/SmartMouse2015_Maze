/** these functions read in a .mz file and parse it into a valid maze*/
#ifndef READ_MAZE_H
#define READ_MAZE_H

#include "maze.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/** overall function to create a maze from file. any error will result in a null return.
* @return a valid maze pointer to the maze struct, null on any sort of error
*/
Maze *read_from_file(FILE *f);

/** prints a maze
* @param maze the maze
*/
void print_maze(Maze *maze);

void print_pointer_maze(Maze *maze);

#endif