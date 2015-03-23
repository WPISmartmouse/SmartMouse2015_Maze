#include "mouse.h"

Mouse *create_mouse(){
	Mouse *mouse = malloc(sizeof(Mouse));
	mouse->row = 0;
	mouse->col = 0;
	mouse->dir = S;
	return mouse;
}

void forward(Mouse *mouse){
	update_pos(mouse->dir, &mouse->row, &mouse->col);
}

void update_pos(Direction dir, int *row, int *col){
	switch(dir){
		case N:(*row)--;break;
		case S:(*row)++;break;
		case E:(*col)++;break;
		case W:(*col)--;break;
	}	
}

char dir_to_char(Direction dir){
	switch(dir){
		case N:return 'N';
		case S:return 'S';
		case E:return 'E';
		case W:return 'W';
	}
}

/**true means a wall exists**/
bool *sense(Maze *maze, Mouse *mouse){
	bool *walls = malloc(4*sizeof(bool));
	bool *w = walls;
	int i;
	Node *n = get_node(maze,mouse->row,mouse->col);
	for (i=0;i<4;i++){
		*(w++) = (n->neighbors[i] == NULL);
	}

	return walls;
}