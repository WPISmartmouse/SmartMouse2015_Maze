#include "mouse.h"

Mouse *create_mouse(){
	Mouse *mouse = malloc(sizeof(Mouse));
	mouse->row = 0;
	mouse->col = 0;
	mouse->dir = S;
	return mouse;
}

void forward(Mouse *mouse){
	switch(mouse->dir){
		case N:mouse->row--;break;
		case S:mouse->row++;break;
		case E:mouse->col++;break;
		case W:mouse->col--;break;
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

bool *sense(Maze *maze, Mouse *mouse){
	bool *walls = malloc(4*sizeof(bool));

	int i;
	Node *n = get_node(maze,mouse->row,mouse->col);
	for (i=0;i<4;i++){
		walls = (n->neighbors[i] == NULL);
	}

	return walls;
}

void setDir(Mouse *mouse,Direction d){
	mouse->dir = d;
}