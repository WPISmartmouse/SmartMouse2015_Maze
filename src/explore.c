#include "maze.h"
#include "maze_io.h"
#include "solvers.h"

int main(){

	srand(time(NULL));

	FILE *f = fopen("mazes/16x16.mz","r");

	Maze *maze = read_from_file(f);

	left_hand_follow(maze);

	return EXIT_SUCCESS;
}