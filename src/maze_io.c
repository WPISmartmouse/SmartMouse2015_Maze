#include "maze_io.h"

Maze *read_from_file(FILE *f){
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

void print_maze(Maze *maze){
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			char s[17];
			if (!maze->base_node[i][j]->south) *(s++) = "__";
			if (!maze->base_node[i][j]->east) *(s++) = "| ";
		}
		*s = '\0';
		printf("%s\n",s);
	}
}