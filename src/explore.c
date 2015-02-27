#include "maze.h"
#include "maze_io.h"
#include "solvers.h"

int main(){

	srand(time(NULL));

	FILE *f = fopen("mazes/16x16.mz","r");

	Maze *maze = read_from_file(f);

	flood_fill(maze);
	
	return EXIT_SUCCESS;
}