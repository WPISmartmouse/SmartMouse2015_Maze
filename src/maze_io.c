#include "maze_io.h"

Maze *read_from_file(FILE *f){
	//check for bad file
	if (!f) return NULL;

	char line[MAZE_SIZE + 1]; //16 spaces and null terminator
	char *success;

	int i;
	for (i=0;i< MAZE_SIZE;i++){ //read in each line
		success = fgets(line, 2 * MAZE_SIZE + 2,f);
		
		if (!success) return NULL;

		printf("successfully read... %s",line);
	}

}

void print_maze(Maze *maze){
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		char *s = calloc(sizeof(char),MAZE_SIZE + 1);
		for (j=0;j<MAZE_SIZE;j++){
			if (!maze->base_node[i][j].west){
				strcpy(s++,"|");
				if (maze->base_node[i][j].south){
					strcpy(s++,"_");
				}
				else {
					strcpy(s++," ");
				}
			}
			else {
				strcpy(s++,"_");
				if (maze->base_node[i][j].south){
					strcpy(s++,"_");
				}
				else {
					strcpy(s++," ");
				}
			}
		}
		*s = '\0';
		printf("%s\n",s);
	}
}