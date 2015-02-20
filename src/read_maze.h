/** these functions read in a .mz file and parse it into a valid maze*/
#ifndef READ_MAZE_H
#define READ_MAZE_H

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>


/** overall function to create a maze from file. any error will result in a null return.
* @return a valid maze pointer to the maze struct, null on any sort of error
*/
Maze maze* read_from_file(FILE *f);

#endif