#include "read_maze.h"

Maze maze* read_from_file(FILE *f){
	//check for bad file
	if (!f) return NULL;

	char line[MAZE_SIZE + 1]; //16 spaces and null terminator
	char *success;

	int i;
	for (i=0;i<MAZE_SIZE;i++){ //read in each line
		success = fgets(line,MAZE_SIZE + 1,f);
		
		if (!success) return NULL;

		printf("successfully read... %s\n",line);
	}



}