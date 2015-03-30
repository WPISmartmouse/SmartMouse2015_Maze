#include "maze.h"
#include "maze_io.h"
#include "solvers.h"
#include <errno.h>
#include <time.h>

void setup()
{
srand(time(NULL));
	char *filename;
	if (argc >= 2){
		filename = argv[1];
	}
	else {
		filename = "mazes/16x16_3.mz";
	}

	FILE *f = fopen(filename,"r");

	if (f == NULL){
		printf("error opening maze file %s %s\n",filename,strerror(errno));
		return EXIT_FAILURE;
	}

	printf("using maze file %s\n",filename);
	Maze *maze = read_from_file(f);

	flood_explore(maze);
	
	free_maze(maze);
	fclose(f);

	return EXIT_SUCCESS;
}

void loop(){
  
}
