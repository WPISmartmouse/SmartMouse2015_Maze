#include "maze.h"
#include "maze_io.h"

int main(){

	FILE *f = fopen("mazes/16x16.mz","r");

	Maze *maze = read_from_file(f);

	return EXIT_SUCCESS;
}