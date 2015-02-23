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

void setDir(Mouse *mouse,Direction d){
	mouse->dir = d;
}