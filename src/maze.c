/** maze.c implements the functions used to create, free, and manipulate maze
*/
#include "maze.h"

Maze *create_maze(){
	Maze *maze = malloc(sizeof(Maze));
	maze->solved = false;
	maze->fastest_route = malloc(MAZE_SIZE*MAZE_SIZE*sizeof(char)); //assume really bad route--visits all squares.
	*maze->base_node = create_node();
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){	
			*(maze->base_node++) = create_node();
		}
	}

}

Node *create_node(){
	Node *node = malloc(sizeof(Node));
	node->known = false;
	node->north=NULL;
	node->south=NULL;
	node->east=NULL;
	node->west=NULL;
	return node;
}

Node *get_node(Maze *maze, int x, int y){
	return &maze->base_node[x][y];
}

bool free_maze(Maze *maze){
	free(maze->fastest_route);
	free(maze->base_node); //you didn't malloc neighbors, so don't free them.
	free(maze);
}

//nothing fancy here, just convenient. might remove if it never gets more complicated
bool free_node(Node *node){
	free(node);	
}
